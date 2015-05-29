module BrainHask.Parser 
( Ins(..)
, parseBH
, toC
)
where

import Text.ParserCombinators.Parsec

import Control.Monad (liftM)

data Ins = Plus 
            | Minus
            | ShiftR
            | ShiftL 
            | Out 
            | In 
            | Loop [Ins]


instance Show Ins where
    show Plus        = "+"
    show Minus       = "-"
    show ShiftR      = ">"
    show ShiftL      = "<"
    show Out         = "."
    show In          = ","
    show (Loop l)    = "[" ++ innerIns ++ "]"
        where
            innerIns :: String
            innerIns = foldl (\acc x -> acc ++ show x) "" l


-- parsing logic
comments :: Parser ()
comments = skipMany1 $ noneOf "+-<>.,[]"

operator :: Parser [Ins]
operator = liftM (map cToIns) $ many1 (oneOf "+-<>.,")
    where 
        cToIns :: Char -> Ins
        cToIns '+' = Plus
        cToIns '-' = Minus
        cToIns '>' = ShiftR
        cToIns '<' = ShiftL
        cToIns '.' = Out
        cToIns ',' = In


expr :: Parser [Ins]
expr = (comments >> return []) <|> operator <|> loop

many1Expr :: Parser [Ins]
many1Expr = liftM concat $ many1 expr

loop :: Parser [Ins]
loop = between (char '[') (char ']') $ liftM (\x -> [Loop x]) loopImpl
    where
        loopImpl :: Parser [Ins]
        loopImpl = many1Expr <|> (comments >> return []) <|> return []


parseBH :: String -> String -> Either ParseError [Ins]
parseBH = parse $ many1Expr <|> return []

-- end parsing


cTab = "    "


toC :: [Ins] -> String
toC l = "#include <stdio.h>\n\
        \#define STACK_SIZE 30000\n\n\
        \int main(int argc, const char * argv[]){\n"
        ++ cTab ++ "char stack[STACK_SIZE];\n"
        ++ cTab ++ "char* sp = stack;\n"
        ++ c ++ cTab ++ "return 0;\n}"
    where 
        c :: String
        c = unlines $ map (cTab ++) fl
        fl :: [String]
        fl = concatMap insToC l
    

insToC :: Ins -> [String]
insToC Plus = ["++*sp;"]
insToC Minus = ["--*sp;"]
insToC ShiftR = ["++sp;"]
insToC ShiftL = ["--sp;"]
insToC Out = ["putchar(*sp);"]
insToC In = ["*sp = getchar();"]
insToC (Loop l) = "while (*sp) {" : lc ++ ["}"]
    where 
        lc :: [String]
        lc = foldl (\acc x -> acc ++ mlc x) [] l
        mlc :: Ins -> [String]
        mlc i = map (cTab ++ ) $ insToC i
