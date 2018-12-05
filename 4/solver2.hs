import Data.List
import Data.IntMap.Lazy

main :: IO ()
main = do
    --filename<-getLine
    inputlist <- fmap lines (readFile "input")
    let parsedInput = (Data.List.map (\x-> if elem '#' x then read(tail x)::Int else read(x)::Int) (clean(sort inputlist)))
    let answer = feedTotalTime parsedInput 0 empty
    print(getAnswer(allGuardsBiggestMinute (assocs(answer)) parsedInput) ((0,0),0))

getAnswer :: [((Int,Int),Int)]-> ((Int,Int),Int) -> Int
getAnswer [] y = (fst(fst y))*(snd(fst y))
getAnswer (x:xs) y
                  |(snd x)>(snd y) = getAnswer xs x
                  |otherwise = getAnswer xs y

allGuardsBiggestMinute :: [(Int,Int)] -> [Int] ->[((Int,Int),Int)]
allGuardsBiggestMinute [] y = []
allGuardsBiggestMinute (x:xs) y = let
                                   a = (isolateGuardRoutine y (fst x) False)
                                   b = reduceMinutes (sort(generateMinutes (dropIntercalate (zip a (tail a)) True))) 0
                                   in [(((fst x),(fst(returnBiggest b (0,0)))),(snd(returnBiggest b (0,0))))] ++ allGuardsBiggestMinute xs y

reduceMinutes :: [Int] -> Int -> [(Int,Int)]
reduceMinutes x 61 = []
reduceMinutes x y = [(y,(length(Data.List.filter (==y) x)))] ++ reduceMinutes x (y+1)

generateMinutes :: [(Int,Int)] -> [Int]
generateMinutes [] = []
generateMinutes (x:xs) = [(fst x)..((snd x)-1)] ++ generateMinutes xs

returnBiggest :: [(Int,Int)] -> (Int,Int) -> (Int,Int)
returnBiggest [] y = y
returnBiggest (x:xs) y
                     |(snd y)>(snd x) = returnBiggest xs y
                     |otherwise = returnBiggest xs x

dropIntercalate :: [a] -> Bool -> [a]
dropIntercalate [] b = []
dropIntercalate (x:xs) b
                       |b == True = [x] ++ dropIntercalate xs False
                       |otherwise = dropIntercalate xs True

clean :: [String] -> [String]
clean [] = []
clean (x:xs)
         |elem 'G' x =  [(takeWhile (/=' ') (drop 25 x))] ++ clean xs
         |otherwise =  [(take 2 (drop 15 x))] ++ clean xs

feedTotalTime :: [Int] -> Int -> IntMap Int -> IntMap Int
feedTotalTime [] y m = m
feedTotalTime (x:xs) y m
                      |(x>60) &&((head xs)>60) = feedTotalTime xs x (insertWith (+) x 0 m)
                      |x>60 = feedTotalTime (drop 2 xs) x (insertWith (+) x ((head(tail xs))-(head xs)) m)
                      |otherwise = feedTotalTime (tail xs) y (insertWith (+) y ((head xs)-x) m)

isolateGuardRoutine :: [Int] -> Int -> Bool -> [Int]
isolateGuardRoutine [] y b = []
isolateGuardRoutine (x:xs) y b 
                    |x == y = isolateGuardRoutine xs y True
                    |(x>60) = isolateGuardRoutine xs y False
                    |b == True = [x] ++ isolateGuardRoutine xs y b
                    |otherwise = isolateGuardRoutine xs y b 
