{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- IndentSpec
-}

module IndentSpec (spec) where

import Test.Hspec ( describe, it, shouldBe, Spec )
import Indent ( addIndent, escapeString, generateIndent )

spec :: Spec
spec = do
    describe "generateIndent" $ do
        it "should generate the correct indentation for level 0" $
            generateIndent 0 `shouldBe` ""

        it "should generate the correct indentation for level 1" $
            generateIndent 1 `shouldBe` "    "

        it "should generate the correct indentation for level 2" $
            generateIndent 2 `shouldBe` "        "

    describe "addIndent" $ do
        it "should add the correct indentation to a line for level 0" $
            addIndent 0 "test" `shouldBe` "test"

        it "should add the correct indentation to a line for level 1" $
            addIndent 1 "test" `shouldBe` "    test"

        it "should add the correct indentation to a line for level 2" $
            addIndent 2 "test" `shouldBe` "        test"

    describe "escapeString" $ do
        it "should escape backslashes in a string" $
            escapeString "foo\\bar" `shouldBe` "foo\\\\bar"

        it "should escape double quotes in a string" $
            escapeString "foo\"bar" `shouldBe` "foo\\\"bar"

        it "should not modify a string without special characters" $
            escapeString "foobar" `shouldBe` "foobar"
