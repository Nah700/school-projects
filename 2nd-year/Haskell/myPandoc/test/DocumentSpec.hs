{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- DocumentSpec
-}

module DocumentSpec (spec) where

import Test.Hspec ( describe, it, shouldBe, shouldNotBe, Spec )
import Document
    ( Document(Document),
      FormattingElement(Bold, Italic),
      Header(Header), Content (Formatting, Text, Paragraph) )

spec :: Spec
spec = do
    describe "Document equality" $ do
        it "should consider two equal documents as equal" $
            let doc1 = Document (Header "Title" Nothing Nothing) []
                doc2 = Document (Header "Title" Nothing Nothing) []
            in doc1 `shouldBe` doc2

        it "should consider two different documents as not equal" $
            let doc1 = Document (Header "Title" Nothing Nothing) []
                doc2 = Document (Header "Different Title" Nothing Nothing) []
            in doc1 `shouldNotBe` doc2

    describe "FormattingElement equality" $ do
        it "should consider two equal formatting elements as equal" $
            let element1 = Italic "text"
                element2 = Italic "text"
            in element1 `shouldBe` element2

        it "should consider two different formatting elements as not equal" $
            let element1 = Italic "text"
                element2 = Bold "text"
            in element1 `shouldNotBe` element2

    describe "Show instances" $ do
        it "should show a Document correctly" $
            let doc = Document (Header "Title" (Just "Author") (Just "Date"))
                               [Text "Text content", Formatting (Bold "Bold text")]
            in show doc `shouldBe` "Document (Header {title = \"Title\", author = Just \"Author\", date = Just \"Date\"}) [Text \"Text content\",Formatting (Bold \"Bold text\")]"

        it "should show a Header correctly" $
            let header = Header "Title" (Just "Author") (Just "Date")
            in show header `shouldBe` "Header {title = \"Title\", author = Just \"Author\", date = Just \"Date\"}"

        it "should show a Content correctly" $
            let content = Paragraph [Text "Paragraph content", Formatting (Italic "Italic text")]
            in show content `shouldBe` "Paragraph [Text \"Paragraph content\",Formatting (Italic \"Italic text\")]"

        it "should show a FormattingElement correctly" $
            let element = Bold "Bold text"
            in show element `shouldBe` "Bold \"Bold text\""
