main :: IO ()
main = do
    filename<-getLine
    inputlist <- fmap lines (readFile filename)
    let list1 = multiplefinder inputlist
    let count2 = counterx list1 2
    let count3 = counterx list1 3
    print(count2*count3)

multiplefinder :: [String] -> [[Int]]
multiplefinder [] = []
multiplefinder (x:xs) = [stringfinder x 'a'] ++ multiplefinder xs

stringfinder :: [Char] -> Char -> [Int]
stringfinder x y 
              |y == 'z' = [length(filter (==y) x)]
              |otherwise = [length(filter (==y) x)] ++ stringfinder x (succ y)

counterx :: [[Int]] -> Int -> Int
counterx [] y = 0
counterx (x:xs) y
             |length(filter (==y) x)>0 = 1 + counterx xs y
             |otherwise = counterx xs y
