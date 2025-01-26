{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- DocumentToXml
-}

module DocumentToXml (
    documentToXml,
    Document,
) where

import Document
    ( Document(..),
    Header(..),
    Content(..),
    FormattingElement(..))

import Indent ( addIndent, escapeString )

textToXml :: String -> String
textToXml str = str

formattingToXml :: FormattingElement -> Int -> String
formattingToXml (Italic str) _ = "<italic>" ++ escapeString str ++
    "</italic>"
formattingToXml (Bold str) _ = "<bold>" ++ escapeString str ++ "</bold>"
formattingToXml (Code str) _ = "<code>" ++ escapeString str ++ "</code>"

linkToXml :: String -> [Content] -> Int -> String
linkToXml url content level =
    "<link url=\"" ++ url ++ "\">" ++
    contentsToXmlArray content False (level + 2) ++ "</link>"

imageToXml :: String -> [Content] -> Int -> String
imageToXml url alt level =
    "<image url=\"" ++ url ++ "\">" ++
    contentsToXmlArray alt False (level + 2) ++ "</image>"

paragraphToXml :: [Content] -> Int -> String
paragraphToXml content level = "<paragraph>" ++
    contentsToXmlArray content False level ++ "</paragraph>"

sectionToXml :: Maybe String -> [Content] -> Int -> String
sectionToXml titleStr content level =
    "<section " ++ finalTitleStr ++ ">" ++
    contentsToXmlArray content False level ++
    "\n" ++ addIndent (level + 1) "</section>"
      where
        finalTitleStr = case titleStr of
          Just titleBeacon -> "title=\"" ++ titleBeacon ++ "\""
          Nothing -> ""

codeBlockToXml :: [Content] -> Int -> String
codeBlockToXml [Text s] _ =
    "<codeblock>" ++ s ++ "</codeblock>"
codeBlockToXml codeLines level =
    "<codeblock>" ++
    commaSeparated (map (`contentConverter` (level + 1)) codeLines) ++
    "\n" ++ addIndent (level + 1) "</codeblock>"

listToXml :: [Content] -> Int -> String
listToXml items level =
    "<list>" ++
    commaSeparated (map (`contentConverter` (level + 1)) items) ++
    "\n" ++ addIndent (level + 1) "</list>"

nextLine :: Int -> String -> String
nextLine level str = '\n' : addIndent (level + 1) str

contentConverter :: Content -> Int -> String
contentConverter (Text str) _ = textToXml str
contentConverter (Formatting format) level = formattingToXml format level
contentConverter (Link url content) level = linkToXml url content level
contentConverter (Image url alt) level = imageToXml url alt level
contentConverter (Paragraph content) l = nextLine l (paragraphToXml content l)
contentConverter (Section t c) l = nextLine l (sectionToXml t c l)
contentConverter (CodeBlock code) l = nextLine l (codeBlockToXml code l)
contentConverter (List items) l = nextLine l (listToXml items l)

contentsToXmlArray :: [Content] -> Bool -> Int -> String
contentsToXmlArray contents indentedStart level =
    (if indentedStart then addIndent level "\n" else "") ++
    commaSeparated (map (`contentConverter` (level + 1)) contents)

commaSeparated :: [String] -> String
commaSeparated [] = ""
commaSeparated [x] = x
commaSeparated (x:xs) = x ++ commaSeparated xs

appendContent :: [Content] -> Int -> String
appendContent [] _ = ""
appendContent (c:cs) l = contentConverter c l ++ appendContent cs l

displayBody :: [Content] -> Int -> String
displayBody content level =
    addIndent level "<body>" ++
    appendContent content level ++
    "\n" ++ addIndent level "</body>\n"

displayHeader :: Header -> String
displayHeader header = addIndent 1 "<header title=\"" ++ title header ++
    "\">" ++ authorStr ++ dateStr ++ "\n" ++ addIndent 1 "</header>\n"
      where
        authorStr = case author header of
          Just a -> "\n" ++ addIndent 2 "<author>" ++ a ++ "</author>"
          Nothing -> ""
        dateStr = case date header of
          Just d -> "\n" ++ addIndent 2 "<date>" ++ d ++ "</date>"
          Nothing -> ""

documentToXml :: Document -> String
documentToXml (Document header content) = "<document>\n" ++
    displayHeader header ++ displayBody content 1 ++ "</document>"
