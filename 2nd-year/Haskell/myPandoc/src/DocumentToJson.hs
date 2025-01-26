{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- DocumentToJson
-}

module DocumentToJson (
    documentToJson,
    Document,
) where

import Document
    ( Document(..),
    Header(..),
    Content(..),
    FormattingElement(..))

import Indent ( addIndent, escapeString )

headerToJson :: Header -> Int -> String
headerToJson (Header titleStr Nothing Nothing) l =
    "{\n" ++
    addIndent (l + 1) ("\"title\": \"" ++ titleStr ++ "\"\n") ++
    addIndent l "}"
headerToJson (Header titleStr au da) l =
    "{\n" ++
    addIndent (l + 1) ("\"title\": \"" ++ titleStr ++ "\",\n") ++
    maybe "" (\a -> addIndent (l + 1) ("\"author\": \"" ++ a ++ "\",\n")) au ++
    maybe "" (\d -> addIndent (l + 1) ("\"date\": \"" ++ d ++ "\"\n")) da ++
    addIndent l "}"

textToJson :: String -> Int -> String
textToJson str level = addIndent level ("\"" ++ escapeString str ++ "\"")

formattingToJson :: FormattingElement -> Int -> String
formattingToJson (Italic str) level =
    addIndent level "{\n" ++
    addIndent (level + 1) ("\"italic\": \"" ++ escapeString str ++ "\"\n") ++
    addIndent level "}"
formattingToJson (Bold str) level =
    addIndent level "{\n" ++
    addIndent (level + 1) ("\"bold\": \"" ++ escapeString str ++ "\"\n") ++
    addIndent level "}"
formattingToJson (Code str) level =
    addIndent level "{\n" ++
    addIndent (level + 1) ("\"code\": \"" ++ escapeString str ++ "\"\n") ++
    addIndent level "}"

linkToJson :: String -> [Content] -> Int -> String
linkToJson url content level =
    addIndent level "{\n" ++
    addIndent (level + 1) "\"link\": {\n" ++
    addIndent (level + 2) ("\"url\": \"" ++ url ++ "\",\n") ++
    addIndent (level + 2) ("\"content\": "
        ++ contentsToJsonArray content False (level + 2) ++ "\n") ++
    addIndent (level + 1) "}\n" ++
    addIndent level "}"

imageToJson :: String -> [Content] -> Int -> String
imageToJson url alt level =
    addIndent level "{\n" ++
    addIndent (level + 1) "\"image\": {\n" ++
    addIndent (level + 2) ("\"url\": \"" ++ url ++ "\",\n") ++
    addIndent (level + 2) ("\"alt\": "
        ++ contentsToJsonArray alt False (level + 2) ++ "\n") ++
    addIndent (level + 1) "}\n" ++
    addIndent level "}"

paragraphToJson :: [Content] -> Int -> String
paragraphToJson content = contentsToJsonArray content True

sectionToJson :: Maybe String -> [Content] -> Int -> String
sectionToJson titleStr content level =
    addIndent level "{\n" ++
    addIndent (level + 1) "\"section\": {\n" ++
    addIndent (level + 2)
        (maybe "" (\t -> "\"title\": \"" ++ t ++ "\",\n") titleStr) ++
    addIndent (level + 2) ("\"content\": "
        ++ contentsToJsonArray content False (level + 2) ++ "\n") ++
    addIndent (level + 1) "}\n" ++
    addIndent level "}"

codeBlockToJson :: [Content] -> Int -> String
codeBlockToJson codeLines level =
    addIndent level "{\n" ++
    addIndent (level + 1) "\"codeblock\": [\n" ++
    commaSeparated (map (`contentToJson` (level + 2)) codeLines) ++ "\n" ++
    addIndent (level + 1) "]\n" ++
    addIndent level "}"

listToJson :: [Content] -> Int -> String
listToJson items level =
    addIndent level "{\n" ++
    addIndent (level + 1) "\"list\": [\n" ++
    commaSeparated (map (`contentToJson` (level + 2)) items) ++ "\n" ++
    addIndent (level + 1) "]\n" ++
    addIndent level "}"

contentToJson :: Content -> Int -> String
contentToJson (Text str) level = textToJson str level
contentToJson (Formatting formatting) level = formattingToJson formatting level
contentToJson (Link url content) level = linkToJson url content level
contentToJson (Image url alt) level = imageToJson url alt level
contentToJson (Paragraph content) level = paragraphToJson content level
contentToJson (Section t c) level = sectionToJson t c level
contentToJson (CodeBlock codeLines) level = codeBlockToJson codeLines level
contentToJson (List items) level = listToJson items level

contentsToJsonArray :: [Content] -> Bool -> Int -> String
contentsToJsonArray contents indentedStart level =
    (if indentedStart then addIndent level "[\n" else "[\n") ++
    commaSeparated (map (`contentToJson` (level + 1)) contents) ++
    "\n" ++
    addIndent level "]"

commaSeparated :: [String] -> String
commaSeparated [] = ""
commaSeparated [x] = x
commaSeparated (x:xs) = x ++ ",\n" ++ commaSeparated xs

documentToJson :: Document -> String
documentToJson (Document header content) =
    "{\n" ++ addIndent 1 "\"header\": " ++
    headerToJson header 1 ++ ",\n" ++
    addIndent 1 "\"body\": " ++ contentsToJsonArray content False 1 ++ "\n}"
