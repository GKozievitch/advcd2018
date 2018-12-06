import Data.Char

main :: IO ()
main = do
    --filename<-getLine
    inputlist <- fmap lines (readFile "input")
    print(length(master (concat inputlist)))

master :: [Char] -> [Char]
master [] = []
master x = let
             a = reducer ((zip x (tail x))++[(last x,' ')])
             in if (length a) == (length x) then x else master a

reducer  :: [(Char,Char)] -> [Char]
reducer [] = []
reducer (x:xs)
              |((fst x)/=(snd x))&&(((Data.Char.toUpper (fst x))==(snd x))||((Data.Char.toLower (fst x))==(snd x))) = reducer (tail xs)
              |otherwise = [(fst x)] ++ reducer xs