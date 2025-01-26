{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- Parsing
-}

module Parsing (
    MyOptions(..),
    getArgsOpt,
    readMyFile,
    module System.Exit,
    myOptionsParser,
    parser,
    checkArgs,
) where

import Options.Applicative
    ( (<**>),
      Parser,
      ParserInfo,
      helper,
      fullDesc,
      header,
      help,
      info,
      long,
      metavar,
      option,
      progDesc,
      short,
      str,
      value,
      execParser )
import Control.Exception ( SomeException(SomeException), catch )
import System.Exit (exitWith, ExitCode (ExitFailure))
import System.IO.Error (catchIOError)

data MyOptions = MyOptions {
    _ifile::FilePath,
    _oformat::String,
    _ofile::FilePath,
    _iformat::String
} deriving (Show, Eq)

myOptionsParser :: Parser MyOptions
myOptionsParser = MyOptions
    <$> option str (short 'i' <> long "ifile" <> metavar "FilePath"
        <> help "path to the file to convert")
    <*> option str (short 'f' <> long "oformat" <> metavar "String"
        <> help "output format (xml, json, markdown)")
    <*> option str (short 'o' <> long "ofile" <> metavar "FilePath"
        <> help "path to the output file" <> value "NULL")
    <*> option str (short 'e' <> long "iformat" <> metavar "String"
        <> help "input format (xml, json, markdown)" <> value "any")

parser :: ParserInfo MyOptions
parser = info (myOptionsParser <**> helper)
  (fullDesc <> progDesc "My Pandoc" <>
   header "Leo the boss.")

checkArgs :: MyOptions -> Maybe MyOptions
checkArgs = Just

getArgsOpt :: IO MyOptions
getArgsOpt = do
    options <- catch
      (execParser parser)
      (\(SomeException _) -> exitWith (ExitFailure 84))
    case checkArgs options of
      Just args -> return args
      Nothing -> exitWith (ExitFailure 84)

readMyFile :: FilePath -> IO [Char]
readMyFile filename = catchIOError (
    do
        content <- readFile filename
        if null content
            then putStrLn "Empty File" >> exitWith (ExitFailure 84)
            else return content
  ) (\_ -> putStrLn "File not found" >> exitWith (ExitFailure 84))