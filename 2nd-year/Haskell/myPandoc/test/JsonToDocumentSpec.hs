{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- JsonToDocumentSpec
-}

module JsonToDocumentSpec (spec) where

import Test.Hspec ( describe, it, shouldBe, shouldSatisfy, Spec )
import JsonToDocument ( jsonToDocument )
import Document
    ( Content(..),
      Document(..),
      FormattingElement(..),
      Header(..) )

spec :: Spec
spec = do
    describe "jsonToDocument" $ do
        it "should parse valid JSON input to a Document" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [\"Content\"]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [Text "Content"]
            in jsonToDocument input `shouldBe` expected

        it "should return Left when input is invalid JSON" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [\"Content\"]"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when title is missing" $
            let input = "{\"header\": {\"body\": [\"Content\"]}}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when body is missing" $
            let input = "{\"header\": {\"title\": \"Title\"}}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when content type is invalid" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": \"Content\"}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should parse document with italic formatting" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [{\"italic\": \"Italic text\"}]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [Formatting (Italic "Italic text")]
            in jsonToDocument input `shouldBe` expected

        it "should parse document with bold formatting" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [{\"bold\": \"Bold text\"}]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [Formatting (Bold "Bold text")]
            in jsonToDocument input `shouldBe` expected

        it "should parse document with code formatting" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [{\"code\": \"Code text\"}]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [Formatting (Code "Code text")]
            in jsonToDocument input `shouldBe` expected

        it "should parse document with link" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [{\"link\": {\"url\": \"https://example.com\", \"content\": [\"Link text\"]}}]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [Link "https://example.com" [Text "Link text"]]
            in jsonToDocument input `shouldBe` expected

        it "should parse document with image" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [{\"image\": {\"url\": \"image.jpg\", \"alt\": [\"Alt text\"]}}]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [Image "image.jpg" [Text "Alt text"]]
            in jsonToDocument input `shouldBe` expected

        it "should parse document with paragraph" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [[\"Paragraph content\"]]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [Paragraph [Text "Paragraph content"]]
            in jsonToDocument input `shouldBe` expected

        it "should parse document with section" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [{\"section\": {\"title\": \"Section title\", \"content\": [\"Section content\"]}}]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [Section (Just "Section title") [Text "Section content"]]
            in jsonToDocument input `shouldBe` expected

        it "should parse document with code block" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [{\"codeblock\": [\"Line 1\", \"Line 2\"]}]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [CodeBlock [Text "Line 1", Text "Line 2"]]
            in jsonToDocument input `shouldBe` expected

        it "should parse document with list" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [{\"list\": [\"Item 1\", \"Item 2\"]}]}"
                expected = Right $ Document (Header "Title" Nothing Nothing) [List [Text "Item 1", Text "Item 2"]]
            in jsonToDocument input `shouldBe` expected

    describe "jsonToDocument error cases" $ do
        it "should return Left for invalid JSON format" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [\"Content\"]"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when title is missing" $
            let input = "{\"header\": {\"body\": [\"Content\"]}}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when body is missing" $
            let input = "{\"header\": {\"title\": \"Title\"}}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when content type is invalid" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": \"Content\"}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when title is not a string" $
            let input = "{\"header\": {\"title\": 123}, \"body\": [\"Content\"]}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when author is not a string" $
            let input = "{\"header\": {\"title\": \"Title\", \"author\": 123}, \"body\": [\"Content\"]}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when date is not a string" $
            let input = "{\"header\": {\"title\": \"Title\", \"date\": 123}, \"body\": [\"Content\"]}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when body content is not an array" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": \"Content\"}"
            in jsonToDocument input `shouldSatisfy` isLeft

        it "should return Left when content within body is not correctly structured" $
            let input = "{\"header\": {\"title\": \"Title\"}, \"body\": [{\"invalid\": \"Content\"}]}"
            in jsonToDocument input `shouldSatisfy` isLeft

isLeft :: Either a b -> Bool
isLeft (Left _) = True
isLeft _ = False
