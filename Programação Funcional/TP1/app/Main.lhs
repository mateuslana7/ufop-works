  Trabalho Prático 1 - Programação Funcional.
==================

Setup inicial
-------------

\begin{code}
module Main where

import Test.HUnit

import Data.List

import Data.Char
\end{code}

Introdução
----------

O objetivo desse trabalho é implementar um conjunto de funções
para simular a execução de um consulta em um banco de dados.
Todos os exercícios podem ser concluídos utilizando funções
presentes nas bibliotecas _Prelude_, _Data.Char_ e _Data.List_.

Uma boa maneira para conhecer e pesquisar o conteúdo de bibliotecas
Haskell é o uso do Hoogle: https://hoogle.haskell.org, uma máquina
de busca em documentação de bibliotecas de Haskell.

Bancos de dados textuais
------------------------

Uma forma de armazenar informação é usando arquivos de texto. Diversos
formatos textuais são utilizados com esse intuito, como por exemplo, o
formato CSV. Nesse trabalho, utilizaremos um formato simples, em que
cada linha representa um registro de banco de dados e cada coluna um
campo de um registro. Um exemplo deste tipo de banco de dados é
apresentado a seguir.

~~~~
Nome Sobrenome Idade
Astrogildo Tibúrcildo 40
Hermergarda Silvinéia 30
Clodoaldo Murtinho 67
Joaquim Manuel 28
~~~~

Observe que, nesse formato, a primeira linha representa o nome de cada
um dos campos que compõe esse banco de dados.

Representamos esse tipo de informação textual usando os seguintes
tipos Haskell:

\begin{code}
type Field = String
type Row   = [Field]
type Table = [Row]
\end{code}

Por questões de simplicidade, representamos todo tipo de informação
como `String`s.

Parsing de tabelas
------------------

Parsing é o processo de conversão de informação representada como uma
sequência de símbolos em uma estrutura de dados.

A primeira tarefa desse trabalho consiste na implementação de uma função
que realiza o parsing de tabelas.

\begin{code}
parseTable :: String -> Table
parseTable = map words . lines  
\end{code}

Sua função deve ser implementada de forma a satisfazer o seguinte caso
de teste.

\begin{code}
table :: String
table = concat [ "Nome Sobrenome Idade\n"
               , "Astrogildo Tibúrcildo 40\n"
               , "Hermergarda Silvinéia 30\n"
               , "Clodoaldo Murtinho 67\n"
               , "Joaquim Manuel 28"]

tableRep :: Table
tableRep = [ ["Nome", "Sobrenome", "Idade"]
           , ["Astrogildo", "Tibúrcildo", "40"]
           , ["Hermergarda", "Silvinéia", "30"] 
           , ["Clodoaldo", "Murtinho", "67"]
           , ["Joaquim", "Manuel", "28"]
           ]


parseTableTest :: Test
parseTableTest = "parseTableTest" ~: parseTable table ~=? tableRep
\end{code}

Tabelas bem formadas
--------------------

Evidentemente, nem todo arquivo de texto consiste de uma tabela válida.
Dizemos que uma tabela é válida se:

1. Sua primeira linha é formada pelos nomes dos campos dessa tabela.

2. Todas as linhas possuem o mesmo número de colunas.

3. O arquivo possui pelo menos duas linhas (uma contendo o nome dos campos
   e outra contendo um registro).

Dadas as restrições acima, implemente a função:

\begin{code}
validTable :: Table -> Bool
validTable xs 
    | sameNumColumns xs && atLeastTwoLines xs = True
    | otherwise = False

sameNumColumns :: [[String]] -> Bool
sameNumColumns (x:xs) = equalsLength xs (length x)
  where
  equalsLength [] _ = True
  equalsLength (y:ys) headLength 
    | (length y == headLength) = equalsLength ys headLength
    | otherwise = False

atLeastTwoLines :: [[String]] -> Bool
atLeastTwoLines dataset
   | (length dataset >= 2) = True
   | otherwise = False
\end{code}

que verifica se uma tabela fornecida como entrada é ou não válida. O seguinte
caso de teste deve ser satisfeito por sua implementação.

\begin{code}
validTableTest :: Test
validTableTest = "validTableTest" ~: validTable tableRep ~=? True
\end{code}


Impressão de resultados
-----------------------

No primeiro exercício, você implementou uma função para converter uma `String`
em um valor de tipo `Table`. O objetivo desse exercício é a conversão de uma
tabela em um formato textual legível. Considerando a tabela apresentada como exemplo,
sua representação em formato legível seria:

~~~~
+-----------+----------+-----+
|NOME       |SOBRENOME |IDADE|
+-----------+----------+-----+
|Astrogildo |Tibúrcildo|40   |
|Hermergarda|Silvinéia |30   |
|Clodoaldo  |Murtinho  |67   |
|Joaquim    |Manuel    |28   |
+-----------+----------+-----+
~~~~~

Observe que no exemplo acima, várias operações foram feitas sobre a tabela de
entrada:

1. O tamanho de cada coluna é dado pelo maior valor presente nesta coluna (incluindo o nome da coluna).

2. Nomes de colunas são expressos utilizando letras maíusculas.

3. Bordas foram adicionadas para delimitar a tabela e facilitar sua leitura.

Para implementar a impressão de tabelas, basta seguir os seguintes passos.

a) Implemente a função

\begin{code}
intercalate' :: a -> [a] -> [a]
intercalate' v [] = [v]
intercalate' v (x:xs) = v:x:intercalate' v xs

ppLine :: [Int] -> String
ppLine = concat.intercalate' "+".map(flip replicate '-') 
\end{code}

que a partir de uma lista contendo os comprimentos de cada campo da tabela, imprime uma linha de cabeçalho.
Utilize o seguinte teste para guiar sua implementação.

\begin{code}
ppLineTest :: Test
ppLineTest = "ppLineTest" ~: ppLine [3,4,2] ~=? "+---+----+--+"
\end{code}

b) Implemente a função

\begin{code}
ppField :: Int -> String -> String
ppField n field = field ++ replicate (n - (length field)) ' '
\end{code}

que a partir do comprimento de um campo, o valor do campo atual retorna o valor do campo devidamente formatado
incluindo espaços adicionais à esquerda. O seguinte caso de teste ilustra o comportamento esperado por essa
função.

\begin{code}
ppFieldTest :: Test
ppFieldTest = "ppFieldTest" ~: ppField 9 "carlos" ~=? "carlos   "
\end{code}

c) Implemente a função

\begin{code}
ppRow :: [(Int, String)] -> String
ppRow [] = "|"  
ppRow (y:ys) = "|" ++ ppField (fst y) (snd y) ++ ppRow ys
\end{code}

que a partir de uma lista de pares, cujo primeiro componente é o tamanho do campo e o segundo o valor do campo,
formata um registro da tabela.

\begin{code}
ppRowTest :: Test
ppRowTest = "ppRowTest" ~: ppRow [(9,"carlos"), (5,"20")] ~=? "|carlos   |20   |"
\end{code}

d) Implemente a função

\begin{code}
fieldSizes :: Table -> [Int]
fieldSizes xs = [maximum (map length x) | x <- transpose xs] 
\end{code}

que calcula o comprimento de cada campo de uma tabela. 

\begin{code}
fieldSizesTest :: Test
fieldSizesTest = "fieldSizesTest" ~: fieldSizes tableRep ~=? [11, 10, 5]
\end{code}

e) De posse de todas as implementações anteriores, combine-as para
produzir a função

\begin{code}
ppTable :: Table -> String
ppTable (x:xs)
  | validTable (x:xs) == True = uppercase (showHeader x (fieldSizes (x:xs))) ++ showDataset xs (fieldSizes (x:xs)) ++ ppLine (fieldSizes (x:xs)) ++ "\n"
  | otherwise = error "Invalid Table"

makeTuples :: [String] -> [Int] -> [(Int, String)]
makeTuples [] _ = []
makeTuples (y:ys) (z:zs) = (z,y) : makeTuples ys zs

showHeader :: [String] -> [Int] -> String
showHeader xs sz = ppLine sz ++ "\n" ++ (ppRow (makeTuples xs sz)) ++ "\n" ++ ppLine sz ++ "\n"

showDataset :: Table -> [Int] -> String
showDataset xs sz = concat [ppRow (makeTuples x sz) ++ "\n" | x <- xs]

uppercase :: String -> String
uppercase = map toUpper

printTable = putStrLn (ppTable tableRep)
\end{code}

que produz a versão legível de dados presentes em uma tabela textual.


Função main
-----------

\begin{code}
tests :: Test
tests = TestList [ parseTableTest
                 , validTableTest
                 , ppLineTest
                 , ppFieldTest 
                 , ppRowTest
                 , fieldSizesTest]
main :: IO ()
main = runTestTT tests >> return ()
\end{code}
