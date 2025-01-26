{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- Spec
-}

import Test.Hspec ( hspec, describe )
import DocumentSpec ( spec )
import DocumentToJsonSpec ( spec )
import DocumentToMarkdownSpec ( spec )
import DocumentToXmlSpec ( spec )
import IndentSpec ( spec )
import JsonParserSpec ( spec )
import JsonToDocumentSpec ( spec )
import XmlParserSpec ( spec )
import XmlToDocumentSpec ( spec )
import ParserDataSpec ( spec )
import ParsingSpec ( spec )

main :: IO ()
main = hspec $ do
    describe "Document module" DocumentSpec.spec
    describe "DocumentToJson module" DocumentToJsonSpec.spec
    describe "DocumentToMarkdown module" DocumentToMarkdownSpec.spec
    describe "DocumentToXml module" DocumentToXmlSpec.spec
    describe "Indent module" IndentSpec.spec
    describe "JsonParser module" JsonParserSpec.spec
    describe "JsonToDocument module" JsonToDocumentSpec.spec
    describe "XmlParser module" XmlParserSpec.spec
    describe "XmlToDocument module" XmlToDocumentSpec.spec
    describe "ParserData module" ParserDataSpec.spec
    describe "Parsing module" ParsingSpec.spec
