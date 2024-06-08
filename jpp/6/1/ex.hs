import Data.List (nub)

binomial :: (Integral n) => n -> n -> n
binomial n 0 = 1
binomial n k
  | n == k = 1
  | otherwise = binomial (n - 1) k + binomial (n - 1) (k - 1)

-----------------------------------------------

binomial2 :: Int -> Int -> Int
binomial2 n k = triangle !! n !! k -- bierze n wiersz z trojkata i k pozycje; !! operator indeksowania
    where
        triangle = iterate next_row [1] -- iteruje (nieskonczenie, ale lazy), [1] to pierwszy argument
        next_row row = zipWith (+) ([0] ++ row) (row ++ [0]) -- zipWith bierze funkcje (np (+)) i naklada ja na nastepne elementy; tamto dodaje zera na poczatek i koniec row

-----------------------------------------------

merge :: Ord a => [a] -> [a] -> [a] -- ord type class
merge xl [] = xl
merge [] yl = yl
merge (x:xl) (y:yl)
    | x <= y = x:merge xl (y:yl)
    | otherwise = y:merge (x:xl) yl

mergesort :: Ord a => [a] -> [a]
mergesort [] = []
mergesort [a] = [a]
mergesort xl = merge (mergesort (first_half xl)) (mergesort (second_half xl))

first_half xl = let { n = length xl} in take (div n 2) xl
second_half xl = let { n = length xl} in drop (div n 2) xl -- porzuca pierwsza polowe elementow

------------------------------------------------

gcde :: (Integral a) => a -> a -> (a, a, a)
gcde 0 b = (b, 0, 1)
gcde a b =
    let (g, x, y) = gcde (mod b a) a in (g, y - (div b a) * x, x)

de :: (Integral a) => a -> a -> (a, a, a)
de a b = let (g, x, y) = gcde a b in (x, y, g)

------------------------------------------------

primeFactors :: (Integral a) => a -> [a]
primeFactors n = factorize n 2

factorize :: (Integral a) => a -> a -> [a]
factorize 1 _ = []
factorize n factor
    | mod n factor == 0 = factor : factorize (div n factor) factor
    | otherwise = factorize n (factor + 1)

------------------------------------------------

gcdi :: Integral a => a -> a -> a
gcdi 0 b = b
gcdi a b = gcdi (mod b a) a

is_coprime :: Integral a => a -> a -> Bool
is_coprime a b = gcdi a b == 1

totient :: Integral a => a -> a
totient n = fromIntegral (length (filter (is_coprime n) [1..n]))

------------------------------------------------

totient2 :: Integral a => a -> a
totient2 n = foldl (\acc p -> div (acc * (p - 1)) p) n (nub (primeFactors n))
-- nub usuwa duplikaty

------------------------------------------------


primes :: Integral a => a -> [a]
primes n = sieve [2..n]
  where
    sieve [] = []
    sieve (x:xs) = x : sieve [y | y <- xs, mod y x /= 0]
