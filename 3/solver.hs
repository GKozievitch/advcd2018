--import Data.IntSet (IntSet)
import Data.Maybe
import Data.List
import qualified Data.Matrix as Matrix



main :: IO ()
main = do
    filename<-getLine
    inputlist <- fmap lines (readFile filename)
    print(counter(filler inputlist ))

counter :: Matrix.Matrix Int -> Int
counter m = lineRead m 1

lineRead :: Matrix.Matrix Int-> Int ->Int
lineRead m x
             |x ==1001 = 0
             |otherwise =  columnRead m x 1 + lineRead m (x+1)

columnRead :: Matrix.Matrix Int -> Int -> Int ->Int
columnRead m x y
             |y == 1001 = 0
             |(Matrix.getElem x y m) > 1 = 1 + columnRead m x (y+1)
             |otherwise =columnRead m x (y+1)

filler :: [String]->Matrix.Matrix Int
filler [] = Matrix.zero 1000 1000
filler (x:xs) = Matrix.elementwiseUnsafe (+) (createMatrix (generateLeftUpEdge(filter (/=' ') x)) (generateRightDownEdge(filter (/=' ') x))) (filler xs)

createMatrix :: (Int,Int) -> (Int,Int) -> Matrix.Matrix Int
createMatrix x y = do
                    let yy = (fst x + fst y, snd x + snd y)
                    Matrix.matrix 1000 1000 (\ (i,j) -> if(i>=(fst x))&&(i<=(fst yy))&&(j>=(snd x))&&(j<=(snd yy))then 1 else 0)


generateLeftUpEdge :: String -> (Int,Int)
generateLeftUpEdge x = do
                        let a = take((fromJust(elemIndex ':' x))) x 
                        let b = drop ((fromJust(elemIndex '@' a))+1) a
                        let c = splitAt (fromJust(elemIndex ',' b)) b
                        let d = read(fst c)::Int
                        let e = read(tail(snd c))::Int
                        (d,e)


generateRightDownEdge :: String -> (Int,Int)
generateRightDownEdge x = do
                        let b = drop ((fromJust(elemIndex ':' x))+1) x
                        let c = splitAt (fromJust(elemIndex 'x' b)) b
                        let d = read(fst c)::Int
                        let e = read(tail(snd c))::Int
                        (d,e)
                        
--todo: run in a computer with infinite memory for an infinite ammount of time to check if this works
