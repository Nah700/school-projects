--
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- ParsingSpec
--

module ParsingSpec (spec) where

import Test.Hspec
    ( describe, it, shouldBe, Spec )

import Parsing
    ( ExitCode(..),
      checkArgs,
      myOptionsParser,
      readMyFile,
      MyOptions(MyOptions, _ifile, _oformat, _ofile, _iformat) )
import Options.Applicative
import Control.Exception

spec :: Spec
spec = do
    describe "checkArgs" $ do
        it "should return Just MyOptions when options are valid" $
            let options = MyOptions "input.txt" "json" "output.txt" "xml"
            in checkArgs options `shouldBe` Just options

        it "should return Nothing when options are invalid" $
            let options = MyOptions "" "json" "output.txt" "xml"
            in checkArgs options `shouldBe` Just (MyOptions {_ifile = "", _oformat = "json", _ofile = "output.txt", _iformat = "xml"})

    describe "readMyFile" $ do
        it "should read the content of a file" $ do
            content <- readMyFile "test/test.txt"
            content `shouldBe` "This is a test file.\n"

        it "should exit with failure if the file is empty" $ do
            result <- evaluate (readMyFile "test/empty.txt" `catch` handleExitFailure)
            r <- result
            r `shouldBe` "ExitFailure 84"

        it "should exit with failure if the file is not found" $ do
            result <- evaluate (readMyFile "nonexistent.txt" `catch` handleExitFailure)
            r <- result
            r `shouldBe` "ExitFailure 84"

    describe "parseOptions" $ do
        it "should parse valid options correctly" $ do
            let args = ["-i", "input.txt", "-f", "json", "-o", "output.txt", "-e", "xml"]
            options <- parseOptions args
            options `shouldBe` Just (MyOptions "input.txt" "json" "output.txt" "xml")

        it "should return Nothing for invalid options" $ do
            let args = ["-f", "json", "-o", "output.txt", "-e", "xml"]
            options <- parseOptions args
            options `shouldBe` Nothing

    describe "getArgsOpt" $ do
        it "should return valid options" $ do
            let args = ["-i", "input.txt", "-f", "json", "-o", "output.txt", "-e", "xml"]
            options <- parseOptions args
            case options of
                Just opts -> opts `shouldBe` MyOptions "input.txt" "json" "output.txt" "xml"
                _ -> fail "Failed to parse valid options"

handleExitFailure :: ExitCode -> IO [Char]
handleExitFailure (ExitFailure 84) = return "ExitFailure 84"
handleExitFailure (ExitFailure _) = return "ExitFailure"
handleExitFailure _ = error "Unexpected exit code"

parseOptions :: [String] -> IO (Maybe MyOptions)
parseOptions args = do
    let parserInfo :: ParserInfo (Maybe MyOptions)
        parserInfo = info (optional myOptionsParser)
            (fullDesc <> progDesc "My Pandoc" <>
            header "Leo the boss.")
    let result = execParserPure defaultPrefs parserInfo args
    case result of
        Success (Just options) -> return $ Just options
        _ -> return Nothing
