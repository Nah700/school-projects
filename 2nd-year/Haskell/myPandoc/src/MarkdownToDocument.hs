{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- MarkdownToDocument
-}

module MarkdownToDocument (
    markdownToDocument
) where

import ParserData ( Parser(runParser) )
import MarkdownParser ( parseHeader, parseBody )
import Document ( Document(..), Header(..) )

markdownToDocument :: String -> Either String Document
markdownToDocument = runMarkdownParser

lookupString :: String -> [(String, String)] -> Either String String
lookupString key obj =
    case lookup key obj of
        Just value -> Right value
        _ -> Left $ "Missing or invalid value for key: " ++ key

interpretHeader :: [(String, String)] -> Either String Header
interpretHeader header = do
    titleStr <- lookupString "title" header
    let authorStr = lookup "author" header
    let dateStr = lookup "date" header
    return $ Header titleStr authorStr dateStr

runMarkdownParser :: String -> Either String Document
runMarkdownParser input = do
    (value, body) <- runParser parseHeader input
    header <- interpretHeader value
    case runParser parseBody body of
        Left err -> Left err
        Right (b, _) -> Right $ Document header b
