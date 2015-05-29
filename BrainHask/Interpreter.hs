module BrainHask.Interpreter
(State (..)
, InterpreterState
, interpret
, interpretWithState
, newState
)
where

import BrainHask.Parser

import Data.Word (Word8)
import Data.Char 


type CellType = Word8
data State = State {
    getLeft  :: [CellType],         -- left part in reverse order for performance
    getCur   :: CellType,           -- current element
    getRight :: [CellType]          -- right part of the array
}

newState :: InterpreterState
newState = return $ State zeros 0 zeros
    where zeros = repeat 0


update :: (CellType -> CellType) -> State -> State
update f (State l x r) = State l (f x) r

forward :: State -> State
forward (State l x (r:rs)) = State (x:l) r rs

backward :: State -> State
backward (State (l:ls) x r) = State ls l (x:r)


type InterpreterState = IO State
interpret :: [Ins] -> InterpreterState
interpret = interpretWithState newState

interpretWithState :: InterpreterState -> [Ins] -> InterpreterState
interpretWithState = foldl interpretIns

-- evaluate single instruction with a given interpreter state
interpretIns :: InterpreterState -> Ins -> InterpreterState
interpretIns is i = is >>= interpretInsImpl i

-- evaluate single instruction with a given state
interpretInsImpl :: Ins -> State -> InterpreterState
interpretInsImpl (Plus) s                = return $ update (+1) s
interpretInsImpl (Minus) s               = return $ update (subtract 1) s
interpretInsImpl (ShiftR) s              = return $ forward s
interpretInsImpl (ShiftL) s              = return $ backward s
interpretInsImpl (Out) s@(State _ x _)   = (putChar . chr . fromEnum $ x) >> return s
interpretInsImpl (In) (State l _ r)      = do 
    c <- getFirstValidChar
    return $ State l (toEnum . ord $ c) r
    where
        getFirstValidChar :: IO Char
        getFirstValidChar = do
            l <- getLine
            if null l then
                getFirstValidChar
            else
                return $ head l
      
interpretInsImpl i@(Loop l) s@(State _ x _)
    | x == 0    = return s
    | otherwise = interpretIns nst i        -- re-evaluate loop with newstate
    where
        nst :: InterpreterState
        nst = foldl interpretIns (return s) l

