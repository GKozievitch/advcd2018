import Data.Char
import Data.Stack
import Data.Bits
import Data.Maybe

--must be compiled with -O

main :: IO ()
main = do
    --filename<-getLine
    inputlist <- fmap lines (readFile "input")
    let string = concat inputlist
    let sanitizedStrings = map (charlocaust string) ['a'..'z']
    print(minimum(walklist sanitizedStrings)-1)

charlocaust :: [Char] -> Char -> [Char]
charlocaust x y = filter (different y) x

walklist :: [String] -> [Integer]
walklist [] = []
walklist (x:xs) = [master x] ++ walklist xs

master :: [Char] -> Integer
master [] = 0
master x = toInteger(stackSize(foldl (stackReducer) (stackPush (stackNew) 'x')  x))

stackReducer  :: Stack Char -> Char -> Stack Char
stackReducer y x
               |match (fromMaybe 'x' (stackPeek y)) x = fst(fromMaybe (y,'a') (stackPop y))
               |otherwise = stackPush y x

--provided by some anon
different a b = (((ord a) .&. 223) /= ((ord b) .&. 223))

match a b = ((ord a) `xor` (ord b)) == 32