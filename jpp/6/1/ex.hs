binomial :: (Integral n) => n -> n -> n
binomial n 0 = 1
binomial n k
  | n == k = 1
  | otherwise = binomial (n - 1) k + binomial (n - 1) (k - 1)


binomial2 :: Int -> Int -> Int
binomial2 n k = triangle !! n !! k -- bierze n wiersz z trojkata i k pozycje; !! operator indeksowania
    where
        triangle = iterate next_row [1] -- iteruje (nieskonczenie, ale lazy), [1] to pierwszy argument
        next_row row = zipWith (+) ([0] ++ row) (row ++ [0]) -- zipWith bierze funkcje (np (+)) i naklada ja na nastepne elementy; tamto dodaje zera na poczatek i koniec row


