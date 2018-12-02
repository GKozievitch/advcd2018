main :: IO ()
main = do
    filename<-getLine
    inputlist <- fmap lines (readFile filename)
    print(finder(generator inputlist))

generator :: [String] -> [[(Char,Char)]]
generator [] = []
generator (x:xs) = map (zip x) xs ++ generator xs

finder :: [[(Char,Char)]]->[Char]
finder [] = []
finder (x:xs)
          |(length(filter (==False) (map (comparetuple) x)))==1 = beautify x
          |otherwise = finder xs

comparetuple :: (Char,Char) -> Bool
comparetuple x
               |(fst x)==(snd x) = True
               |otherwise = False

beautify :: [(Char,Char)]->[Char]
beautify [] = []
beautify (x:xs)
             |comparetuple x = [fst x] ++ beautify xs
             |otherwise = beautify xs