import Data.IntSet (IntSet)
import qualified Data.IntSet as IntSet

main :: IO ()
main = do
    filename<-getLine
    inputlist <- fmap lines (readFile filename)
    let convertedList = map convert inputlist
    let genlist = makeStateList (cycle convertedList) 0
    print (setFind genlist IntSet.empty)

setFind :: [Int]->IntSet->Int
setFind (x:xs) y
            |IntSet.member x y == True = x
            |otherwise = setFind xs (IntSet.insert x y)

convert :: [Char]->Int
convert (x:xs)
     |x == '+' = read(xs)::Int
     |otherwise = read(x:xs)::Int

makeStateList :: [Int]->Int->[Int]
makeStateList (x:xs) acc =  [acc] ++ makeStateList xs (acc+x)
