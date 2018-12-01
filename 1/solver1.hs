main :: IO ()
main = do
    filename<-getLine
    inputlist <- fmap lines (readFile filename)
    print (sumOf inputlist)
    

sumOf :: [String]->Int
sumOf x = foldr(+) 0 (map convert x)


convert :: [Char]->Int
convert (x:xs)
     |x == '+' = read(xs)::Int
     |otherwise = read(x:xs)::Int