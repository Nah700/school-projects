{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- XmlParserSpec
-}

module XmlParserSpec (spec) where

import Test.Hspec ( describe, it, shouldBe, shouldSatisfy, Spec )
import XmlParser
    ( parseAttributes,
      parseQuotedString,
      parseString,
      parseXmlElement,
      parseXmlText,
      XmlValue(XmlText, XmlElement) )
import ParserData ( Parser(runParser) )

spec :: Spec
spec = do
    describe "parseXmlElement" $ do
        it "should parse a simple XML element" $
            let input = "<tag>content</tag>"
                expected = Right $ XmlElement "tag" [] [XmlText "content"]
            in parseParser parseXmlElement input `shouldBe` expected

        it "should parse an XML element with attributes" $
            let input = "<tag attr1=\"value1\" attr2=\"value2\">content</tag>"
                expected = Right $ XmlElement "tag" [("attr1", "value1"), ("attr2", "value2")] [XmlText "content"]
            in parseParser parseXmlElement input `shouldBe` expected

        it "should parse nested XML elements" $
            let input = "<parent><child>content</child></parent>"
                expected = Right $ XmlElement "parent" [] [XmlElement "child" [] [XmlText "content"]]
            in parseParser parseXmlElement input `shouldBe` expected

        it "should handle whitespace between elements" $
            let input = "<tag1>content1</tag1>  \n  <tag2>content2</tag2>"
                expected = Right $ XmlElement "tag1" [] [XmlText "content1"]
            in parseParser parseXmlElement input `shouldBe` expected

        -- it "should handle self-closing tags" $
        --     let input = "<empty />"
        --         expected = Right $ XmlElement "empty" [] []
        --     in parseParser parseXmlElement input `shouldBe` expected

        it "should fail when start tag and end tag mismatch" $
            let input = "<tag>content</notTag>"
            in parseParser parseXmlElement input `shouldSatisfy` isLeft

    describe "parseXmlText" $ do
        it "should parse text content within an XML element" $
            let input = "content"
                expected = Right $ XmlText "content"
            in parseParser parseXmlText input `shouldBe` expected

        it "should parse text content with special characters" $
            let input = "special &amp; characters"
                expected = Right $ XmlText "special &amp; characters"
            in parseParser parseXmlText input `shouldBe` expected

    describe "parseXmlAttribute" $ do
        it "should parse attributes within an XML start tag" $
            let input = "attr=\"value\""
                expected = Right [("attr", "value")]
            in parseParser parseAttributes input `shouldBe` expected

        it "should parse multiple attributes within an XML start tag" $
            let input = "attr1=\"value1\" attr2=\"value2\""
                expected = Right [("attr1", "value1"), ("attr2", "value2")]
            in parseParser parseAttributes input `shouldBe` expected

        -- it "should fail when attribute value is missing" $
        --     let input = "attr="
        --     in parseParser parseAttributes input `shouldSatisfy` isLeft

    describe "parseString" $ do
        it "should parse plain text content" $
            let input = "plain text"
                expected = Right "plain text"
            in parseParser parseString input `shouldBe` expected

        it "should fail when the input string is empty" $
            let input = ""
            in parseParser parseString input `shouldSatisfy` isLeft

    describe "parseQuotedString" $ do
        it "should parse text within double quotes" $
            let input = "\"text\""
                expected = Right "text"
            in parseParser parseQuotedString input `shouldBe` expected

        -- it "should fail when the quoted string is empty" $
        --     let input = "\"\""
        --     in parseParser parseQuotedString input `shouldSatisfy` isLeft

isLeft :: Either a b -> Bool
isLeft (Left _) = True
isLeft _ = False

parseParser :: Parser a -> String -> Either String a
parseParser parser input = case runParser parser input of
    Left err -> Left err
    Right (value, _) -> Right value
