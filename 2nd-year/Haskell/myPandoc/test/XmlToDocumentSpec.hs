{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- XmlToDocumentSpec
-}

module XmlToDocumentSpec (spec) where

import Test.Hspec ( Spec, describe, it, shouldBe, shouldSatisfy )
import XmlToDocument
    ( interpretElement,
      interpretHeader,
      interpretXmlValue,
      parseBodyElement,
      xmlToDocument,
      lookupSpecificElem,
      getBodyValues )
import XmlParser ( XmlValue(XmlElement, XmlText) )
import Document
    ( Content(Text, Formatting, Link, Image, Paragraph, Section, CodeBlock, List),
      FormattingElement(Italic, Bold, Code),
      Header(Header) )

spec :: Spec
spec = do
    describe "interpretXmlValue" $ do
        it "should fail to interpret an invalid XML document" $
            let input = XmlElement "document" [] [XmlElement "header" [] [], XmlElement "body" [] []]
            in interpretXmlValue input `shouldSatisfy` isLeft

        it "should fail when the XML element is not a document" $
            let input = XmlElement "notdocument" [] []
            in interpretXmlValue input `shouldSatisfy` isLeft

    describe "interpretHeader" $ do
        it "should skip wrong header attributes" $
            let elems = [XmlElement "header" [("title", "Title"), ("author", "Author"), ("date", "Date")] []]
                expected = Right $ Header "Title" Nothing Nothing
            in interpretHeader elems `shouldBe` expected

        it "should handle missing author and date attributes" $
            let elems = [XmlElement "header" [("title", "Title")] []]
                expected = Right $ Header "Title" Nothing Nothing
            in interpretHeader elems `shouldBe` expected

        it "should fail when header element is not found" $
            interpretHeader [] `shouldSatisfy` isLeft

    describe "interpretElement" $ do
        it "should interpret paragraph element" $
            let e = XmlElement "paragraph" [] [XmlText "Content"]
                expected = Right $ Paragraph [Text "Content"]
            in interpretElement e `shouldBe` expected

        it "should interpret section element" $
            let e = XmlElement "section" [("title", "Title")] [XmlElement "paragraph" [] [XmlText "Content"]]
                expected = Right $ Section (Just "Title") [Paragraph [Text "Content"]]
            in interpretElement e `shouldBe` expected

        it "should interpret formatted text element - bold" $
            let e = XmlElement "bold" [] [XmlText "Bold Text"]
                expected = Right $ Formatting (Bold "Bold Text")
            in interpretElement e `shouldBe` expected

        it "should interpret formatted text element - italic" $
            let e = XmlElement "italic" [] [XmlText "Italic Text"]
                expected = Right $ Formatting (Italic "Italic Text")
            in interpretElement e `shouldBe` expected

        it "should interpret formatted text element - code" $
            let e = XmlElement "code" [] [XmlText "Code Text"]
                expected = Right $ Formatting (Code "Code Text")
            in interpretElement e `shouldBe` expected

        it "should interpret code block element" $
            let e = XmlElement "codeblock" [] [XmlText "Code Block Content"]
                expected = Right $ CodeBlock [Text "Code Block Content"]
            in interpretElement e `shouldBe` expected

        it "should interpret list element" $
            let listElem = XmlElement "list" [] [XmlElement "paragraph" [] [XmlText "Item 1"], XmlElement "paragraph" [] [XmlText "Item 2"]]
                expected = Right $ List [Paragraph [Text "Item 1"], Paragraph [Text "Item 2"]]
            in interpretElement listElem `shouldBe` expected

        it "should interpret link element" $
            let e = XmlElement "link" [("url", "URL")] [XmlElement "paragraph" [] [XmlText "Link Text"]]
                expected = Right $ Link "URL" [Paragraph [Text "Link Text"]]
            in interpretElement e `shouldBe` expected

        it "should interpret image element" $
            let e = XmlElement "image" [("url", "URL")] [XmlElement "paragraph" [] [XmlText "Alt Text"]]
                expected = Right $ Image "URL" [Paragraph [Text "Alt Text"]]
            in interpretElement e `shouldBe` expected

        it "should interpret text element" $
            let e = XmlText "Text Content"
                expected = Right $ Text "Text Content"
            in interpretElement e `shouldBe` expected

    describe "parseBodyElement" $ do
        it "should parse a text body element" $
            let e = XmlText "Text Content"
                expected = Right $ Text "Text Content"
            in parseBodyElement e `shouldBe` expected

        it "should parse other XML elements within the body" $
            let e = XmlElement "paragraph" [] [XmlText "Content"]
                expected = Right $ Paragraph [Text "Content"]
            in parseBodyElement e `shouldBe` expected

        it "should fail when the XML element is invalid" $
            let e = XmlElement "invalid" [] []
            in parseBodyElement e `shouldSatisfy` isLeft

        it "should parse a code block body element" $
            let e = XmlElement "codeblock" [] [XmlText "Code Block Content"]
                expected = Right $ CodeBlock [Text "Code Block Content"]
            in parseBodyElement e `shouldBe` expected

        it "should parse a list body element" $
            let listElem = XmlElement "list" [] [XmlElement "paragraph" [] [XmlText "Item 1"], XmlElement "paragraph" [] [XmlText "Item 2"]]
                expected = Right $ List [Paragraph [Text "Item 1"], Paragraph [Text "Item 2"]]
            in parseBodyElement listElem `shouldBe` expected

    describe "xmlToDocument" $ do
        it "should fail to interpret invalid XML documents" $
            let input = "<notdocument></notdocument>"
            in xmlToDocument input `shouldSatisfy` isLeft

        it "should handle XML documents with missing or incorrect attributes" $
            let input = "<document><header><title>Title</title></header><body></body></document>"
            in xmlToDocument input `shouldSatisfy` isLeft

        it "should handle XML documents with unexpected elements" $
            let input = "<document><header><title>Title</title></header><body><unexpected></unexpected></body></document>"
            in xmlToDocument input `shouldSatisfy` isLeft

    describe "lookupSpecificElem" $ do
        it "should return Just the desired element when key matches" $
            let elems = [XmlElement "elem1" [] [], XmlElement "elem2" [] [], XmlElement "elem3" [] []]
            in lookupSpecificElem "elem2" elems `shouldBe` Just (XmlElement "elem2" [] [])

        it "should return Nothing when key doesn't match" $
            let elems = [XmlElement "elem1" [] [], XmlElement "elem2" [] [], XmlElement "elem3" [] []]
            in lookupSpecificElem "notfound" elems `shouldBe` Nothing

        it "should return Nothing when list is empty" $
            lookupSpecificElem "key" [] `shouldBe` Nothing

    describe "getBodyValues" $ do
        it "should return the body values when body element is found" $
            let elems = [XmlElement "body" [] [XmlText "text1", XmlText "text2"]]
            in getBodyValues elems `shouldBe` Right [XmlText "text1", XmlText "text2"]

        it "should return an empty list when body element is not found" $
            let elems = [XmlElement "other" [] []]
            in getBodyValues elems `shouldBe` Left "body not found"

isLeft :: Either a b -> Bool
isLeft (Left _) = True
isLeft _ = False
