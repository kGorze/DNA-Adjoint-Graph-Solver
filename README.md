# Projekt: Analiza i Transformacje Grafów

## Spis treści
1. [Wprowadzenie](#wprowadzenie)  
2. [Struktura projektu](#struktura-projektu)  
3. [Funkcjonalności i główne komponenty](#funkcjonalności-i-główne-komponenty)  
4. [Opis plików źródłowych](#opis-plików-źródłowych)  
5. [Kompilacja i uruchomienie](#kompilacja-i-uruchomienie)  
6. [Sposób użycia](#sposób-użycia)  
7. [Testy jednostkowe](#testy-jednostkowe)  
8. [Uwagi końcowe](#uwagi-końcowe)  

## Wprowadzenie

Niniejszy projekt ilustruje implementację różnych operacji na grafach z użyciem języka C++ – od wczytywania i zapisywania grafów, po weryfikację, czy dany graf jest m.in. *grafem liniowym* (ang. *line graph*) czy *grafem sprzężonym* (ang. *adjoint graph*). Zapewnia też mechanizm tworzenia plików `.dot` do wizualizacji w narzędziu **Graphviz**. Zadanie 2 na labolatoria do prof. Kasprzak - Bioinformatyka 3 semestr, Algorytmy kombinatoryczne w bioinformatyce.

**Cechy projektu**:
- Wczytywanie grafu z pliku, zapisywanie w formatach tekstowym i `.dot`.
- Wsparcie dla wizualizacji (wywołanie narzędzia `dot` do wygenerowania obrazu).
- Detekcja pewnych cech strukturalnych (np. *isAdjointGraph*, *isLinearGraph*).
- Transformacja grafu sprzężonego na jego oryginał (`transformToOriginalGraph`).
- Zbiór testów jednostkowych sprawdzających poprawność operacji.

## Struktura projektu

```
.
├── include/
│   ├── graph.h                // Deklaracja klasy Graph
│   └── test_graph.h           // Deklaracja klasy TestGraph (testy)
├── src/
│   ├── graph.cpp              // Implementacja klasy Graph
│   ├── main.cpp               // Funkcja main - uruchamia logikę programu
│   ├── test_graph.cpp         // Implementacja testów jednostkowych
│   └── ...
└── CMakeLists.txt             // Plik konfiguracyjny CMake (opcjonalnie)
```

## Funkcjonalności i główne komponenty

### 1. Wczytywanie i zapisywanie grafu
- Metoda `readGraphFromFile(const std::string&)` umożliwia odczytanie liczby wierzchołków i ich sąsiadów z pliku tekstowego.  
- Metody `writeGraphToFile(...)` oraz `writeGraphToDotFile(...)` pozwalają zapisać graf w formie tekstowej bądź do pliku `.dot`.

### 2. Wyświetlanie i wizualizacja
- `displayGraph()` – wypisuje na konsolę listę sąsiedztwa.  
- `visualizeGraph(dotFilename, outputImage)` – wywołuje zewnętrzny program `dot`, generując obraz PNG.

### 3. Analiza strukturalna
- `isAdjointGraph()` – sprawdza, czy dany graf może być grafem sprzężonym innego grafu.  
- `isOneGraph()` – weryfikuje, czy wierzchołki nie powielają krawędzi (wskazuje tzw. 1-graf).  
- `isLinearGraph()` – sprawdza, czy graf jest "liniowy" poprzez wykrywanie struktur zabronionych (metody `hasFirstStructure`, `hasSecondStructure`, `hasThirdStructure`).

### 4. Transformacja
- `transformToOriginalGraph()` – jeżeli graf okaże się być sprzężony, można uzyskać jego graf oryginalny.

### 5. Testy
- W pliku `test_graph.cpp` znajdują się testy jednostkowe, wywoływane przez `TestGraph::runAllTests()`.  
- Obejmują między innymi:
  - Poprawność wczytywania/zapisywania
  - Weryfikację metod `isAdjointGraph`, `isOneGraph`, `isLinearGraph`  
  - Sprawdzanie struktur zabronionych.

## Opis plików źródłowych

### 1. `graph.cpp` / `graph.h`
Klasa **Graph** zawiera:
- **Pola**:  
  - `numVertices` – liczba wierzchołków.  
  - `adjacencyList` – wektor wektorów (lista sąsiedztwa).
- **Metody** (wybrane):  
  - `readGraphFromFile(...)` – odczyt i budowa listy sąsiedztwa.  
  - `writeGraphToFile(...)`, `writeGraphToDotFile(...)` – zapis grafu.  
  - `visualizeGraph(...)` – wywołanie Graphviz do stworzenia obrazu.  
  - `isAdjointGraph()`, `isOneGraph()`, `isLinearGraph()` – analiza cech.  
  - `transformToOriginalGraph()` – tworzenie oryginalnego grafu z grafu sprzężonego.

### 2. `main.cpp`
- Główna funkcja programu:  
  - Tworzy obiekt `Graph g`  
  - Wczytuje graf z pliku `input.txt`  
  - Wyświetla go, próbuje ustalić, czy jest *adjoint*, i ewentualnie przekształca go w oryginał.  
  - Zapisuje wyniki do plików `output.txt`, `output_graph.dot`, `output_graph.png`.

### 3. `test_graph.cpp` / `test_graph.h`
- Klasa `TestGraph` zawiera zestaw **testów jednostkowych**:
  - `testFileIO()`, `testSuccessors()`, `testIsAdjointGraph()`, `testIsOneGraph()`, `testLinearStructures()`, itd.  
  - Metoda `runAllTests()` wywołuje je sekwencyjnie.  
  - Plik generuje tymczasowe pliki testowe i porządkuje je po wykonaniu.

## Kompilacja i uruchomienie

1. **Kompilacja** (jeśli używamy CMake):  
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
   Powstanie plik wykonywalny (np. `graph_app`).

2. **Uruchomienie**:  
   ```bash
   ./graph_app
   ```
   lub inna nazwa binarki w zależności od `CMakeLists.txt`.

3. **Wymagania**:
   - Kompilator C++ (np. g++ z obsługą C++11 lub nowszego).  
   - (Opcjonalnie) **Graphviz** (dla metody `visualizeGraph` – wywołanie `dot`).

## Sposób użycia

1. **Przygotowanie pliku wejściowego** (np. `input.txt`):
   - Pierwsza linia: liczba wierzchołków, np. `4`.  
   - Kolejne linie: `wierzchołek: lista_sąsiadów`, np.  
     ```
     1: 2 3
     2: 1 3
     3: 1 2 4
     4: 3
     ```

2. **Uruchomienie programu**:  
   - Program wczyta `input.txt`, wyświetli na konsoli graf, utworzy plik `.dot` i obraz `.png`.
   - Ustali, czy graf jest sprzężony (`adjoint`), a jeżeli tak, przetransformuje do oryginalnego grafu i zapisze w `output.txt`.

3. **Testy**:  
   - Aby włączyć testy, ustaw w `main.cpp` wartość `run_tests = true`.  
   - Skrypt testowy wygeneruje tymczasowe pliki i wywoła zestaw asercji.

## Testy jednostkowe

- W pliku `test_graph.cpp` znajdują się testy do weryfikacji każdej ważniejszej metody:  
  - **I/O** plików: sprawdzanie, czy wczytanie i zapis dają oczekiwany wynik.  
  - **Struktury**: testy `isAdjointGraph`, `isOneGraph`, `isLinearGraph`.  
  - **Struktury zabronione**: `hasFirstStructure()`, `hasSecondStructure()`, `hasThirdStructure()`.  
- Po zakończeniu testów pliki tymczasowe są usuwane (metoda `cleanup()`).

## Uwagi końcowe

- Projekt ten służy jako **przykład** implementacji różnorodnych operacji na grafach (line graph, adjacency checks, transformacje).  
- W **katalogu** z wynikiem (`.dot`) można uruchomić np.:
  ```bash
  dot -Tpng input_graph.dot -o input_graph.png
  ```
  by wygenerować obraz. Metoda `visualizeGraph` robi to automatycznie, zakładając, że `dot` jest zainstalowany i dostępny w ścieżce systemowej.

**Kontakt**:  
- Autor: *Konrad Gorzelańczyk*
- Data: 2025