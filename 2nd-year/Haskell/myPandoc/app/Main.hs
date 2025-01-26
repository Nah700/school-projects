{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- Main
-}

import JsonToDocument (jsonToDocument)
import DocumentToJson (documentToJson, Document)
import XmlToDocument (xmlToDocument)
import DocumentToXml (documentToXml)
import MarkdownToDocument (markdownToDocument)
import DocumentToMarkdown (documentToMarkdown)
import Parsing

printResult :: String -> FilePath -> IO ()
printResult result "NULL" = putStrLn result
printResult result file = writeFile file result

parseAnyFormat :: [Char] -> Either String Document
parseAnyFormat content =
    case jsonToDocument content of
        Right result -> Right result
        Left _ -> case xmlToDocument content of
            Right result -> Right result
            Left _ -> case markdownToDocument content of
                Right result -> Right result
                Left _ ->  Left "Not any good format in"

parseDocument :: String -> [Char] -> Either String Document
parseDocument format content = case format of
    "json" -> jsonToDocument content
    "markdown" -> markdownToDocument content
    "xml"  -> xmlToDocument content
    "any" -> parseAnyFormat content
    _ -> Left "Bad format in"

main :: IO ()
main = do
    args <- getArgsOpt
    content <- readMyFile (_ifile args)
    case parseDocument (_iformat args) content of
        Left err -> putStrLn ("Failure: " ++ err) >> exitWith (ExitFailure 84)
        Right d -> case _oformat args of
            "json" -> printResult (documentToJson d) (_ofile args)
            "markdown" -> printResult (documentToMarkdown d) (_ofile args)
            "xml" -> printResult (documentToXml d) (_ofile args)
            _ -> putStrLn "Bad format out" >> exitWith (ExitFailure 84)
