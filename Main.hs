module Main where

import System.Environment (getArgs)
import System.IO
import Data.List (isSuffixOf)
import System.Console.Docopt
import System.Console.Docopt.NoTH
import System.FilePath (takeFileName, replaceExtension, joinPath)
import Control.Monad (when, forM_, liftM, void, unless)

import BrainHask.Parser (Ins, parseBH, toC)
import BrainHask.Interpreter (interpret, interpretWithState, InterpreterState, newState)


processFile :: Maybe FilePath -> FilePath -> IO ()
processFile outDir fp =
  parsedBf >>= checkParsed (\ast -> interpret ast >> writeToC outDir ast)
  where
    checkParsed :: ([Ins] -> IO ()) -> Either ParseError [Ins] -> IO ()
    checkParsed f (Right ast) = f ast
    checkParsed _ (Left err)  = print err

    parsedBf :: IO (Either ParseError [Ins])
    parsedBf = liftM (parseBH fp) $ readFile fp

    writeToC :: Maybe FilePath -> [Ins] -> IO ()
    writeToC (Just dir) ast = writeFile (newFp dir) $ toC ast
    writeToC _          _   = return ()

    newFp :: FilePath -> FilePath
    newFp dir = joinPath $ dir:[newFn]

    newFn :: FilePath
    newFn = replaceExtension fn ".c"

    fn :: FilePath
    fn = takeFileName fp


cliInterpreter :: String -> InterpreterState -> IO ()
cliInterpreter b s = do
  hFlush stdout
  putStr "*> "
  hFlush stdout
  l <- getLine
  unless (l == "quit") $
    if "\\" `isSuffixOf` l then
      cliInterpreter (b ++ l) s
    else
      case parseBH "user-input" (b ++ l) of
        (Right ast) -> interpretWithState s ast >>= cliInterpreter "" . return
        (Left err)  -> print err >> cliInterpreter b s


main = do
  usageStr <- readFile "./USAGE.docopt"
  doc <- parseUsageOrExit usageStr
  opts <- parseArgsOrExit doc =<< getArgs

  when (opts `isPresent` longOption "help") $  exitWithUsage doc
  
  if null $ getFiles opts then
    cliInterpreter "" newState
  else
    forM_ (getFiles opts) (processFile $ getOutDir opts)

  where
    getOutDir :: Arguments -> Maybe FilePath
    getOutDir opts = opts `getArg` longOption "toC"
    
    getFiles :: Arguments -> [String]
    getFiles opts = opts `getAllArgs` argument "files"
