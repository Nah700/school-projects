{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-compressor-nahim.kandari
-- File description:
-- Algorithme
-}

module Algorithme (launchAlgo, sortFunc) where

import Includes
import Data.List (elemIndex)
import System.Random (randomRIO)
import Utilityfunctions (calculateDistance)

chooseColor :: IO Color
chooseColor = do
    r <- randomRIO (0, 255) :: IO Int
    g <- randomRIO (0, 255) :: IO Int
    b <- randomRIO (0, 255) :: IO Int
    return (Color (r, g, b))

createChoosedColors :: Int -> IO [Color]
createChoosedColors nn = getRandomColor nn []

getRandomColor :: Int -> [Color] -> IO [Color]
getRandomColor no colors
    | no <= 0 = return colors
    | otherwise = do
        papy <- chooseColor
        leo <- getRandomColor (no - 1) colors
        return (papy:leo)

filtreColors :: [Point] -> Float -> [Color] -> [Color]
filtreColors points ll choosedcol
    | distance < ll = rechocolors
    | otherwise = filtreColors points ll rechocolors
    where
        rechocolors = map (getMoyenne . map color) (sortFunc points choosedcol)
        distance = maximum (zipWith calculateDistance choosedcol rechocolors)

sortFunc :: [Point] -> [Color] -> [[Point]]
sortFunc points colors = foldl (\acc point
    -> (getClosestColor point colors acc)) (createCluster colors) points

createCluster :: [Color] -> [[Point]]
createCluster = map (\color -> [])

getClosestColor :: Point -> [Color] -> [[Point]] -> [[Point]]
getClosestColor point colors pointss = case getClosestIndex (color point)
    colors of
    Just index -> let (before, after) = splitAt index pointss in before
        ++ [point:head after] ++ tail after
    Nothing -> pointss

getClosestIndex :: Color -> [Color] -> Maybe Int
getClosestIndex _ [] = Nothing
getClosestIndex couleur couleurs =
    let distances = getColorsDistancesForColor couleur couleurs
    in elemIndex (minimum distances) distances

getColorsDistancesForColor :: Color -> [Color] -> [Float]
getColorsDistancesForColor color = map (calculateDistance color)

getMoyenne :: [Color] -> Color
getMoyenne couleur = Color (r `div` n, g `div` n, b `div` n)
    where
        (r, g, b) = foldl (\(a, b, c) (Color (x, y, z))
            -> (a + x, b + y, c + z)) (0, 0, 0) couleur
        n = length couleur

launchAlgo :: [Point] -> Int -> Float -> IO [Color]
launchAlgo pts nn ll = createChoosedColors nn >>= \guillame -> return $
    filtreColors pts ll guillame
