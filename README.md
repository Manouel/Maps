# Maps

## FlaggedMap

La classe `FlaggedMap` représente une `map` dans laquelle il est possible de récupérer plusieurs éléments à l'aide d'un système de flags. Les paramètres de la classe sont ceux de la `map`, la clé étant les flags et représentant les indices.

Dans l'exemple suivant, on a un ensemble de fichiers classés en différentes catégories, qui représentent les fichiers contenus dans le dossier principal de lecture, les fichiers importés depuis d'autres chemins et les fichiers distants. La clé de la `FlaggedMap` sera donc la catégorie, et la valeur une liste de fichiers.

```cpp
enum FileType { DIRECTORY = 1, IMPORTED = 2,
                LOCAL = DIRECTORY | IMPORTED,
                REMOTE = 4,
                ALL = LOCAL | REMOTE };

FileType operator|(const FileType& t1, const FileType& t2)
{
    return static_cast<FileType>(static_cast<int>(t1) | static_cast<int>(t2));
}

int main()
{
    FlaggedMap<FileType, std::vector<File>> files({DIRECTORY, IMPORTED, REMOTE});
   
    std::map<FileType, std::vector<File>*> directoryFiles = files.getSubSets(DIRECTORY);    // Directory files
   
    std::cout << "List of local files :" << std::endl;
   
    std::map<FileType, std::vector<File>*> localFiles = files.getSubSets(LOCAL);            // = (DIRECTORY | IMPORTED)
    for (auto it = localFiles.begin(); it != localFiles.end(); ++it)
    {
        for (File f : *it->second)
            std::cout << f.getPath() << std::endl;
    }

    return 0;
}
```

Le constructeur de `FlaggedMap` prend en paramètre la liste des flags atomiques (ici `DIRECTORY`, `IMPORTED` et `REMOTE`), dans une liste d'initialisation ou bien dans un vecteur.

```cpp
FlaggedMap(const std::vector<Key>& flags);
FlaggedMap(const std::initializer_list<Key>& flags);
```

Une méthode `getSubSets` permet ensuite de récupérer les catégories correspondant à la clé envoyée en paramètre, qui peut représenter un seul élément de la map (équivaut à y accéder depuis l'opérateur []), ou qui peut être une clé composée.

```cpp
virtual std::map<Key, Value*> getSubSets(const Key& composedKey);
virtual std::map<Key, const Value*> getSubSets(const Key& composedKey) const;
```

Dans l'exemple ci-dessus, l'ensemble des fichiers locaux est récupéré (valeurs `DIRECTORY` et `IMPORTED` de la map), le tout étant retourné dans un sous-ensemble de la `FlaggedMap`.

A noter que l'opérateur [] a été redéfini afin d'empêcher d'affecter des valeurs aux clés composées qui n'ont pas été passées au constructeur de l'objet.

```cpp
virtual Value& operator[](const Key& k);
```

## ComposedMap

La classe `FlaggedMap` représente une `map` dont les valeurs sont des conteneurs (`vector`, `map`...). Utilisée pour stocker des sous-ensembles d'éléments triés par clés, elle permet d'itérer de façon transparente sur l'ensemble des éléments, comme le présente le code suivant.

```cpp
enum class FruitType { APPLE, ORANGE };
 
ComposedMap<FruitType, std::vector<Fruit>> fruits;
fruits[APPLE] = { ... };
fruits[ORANGE] = { ... };
 
unsigned int totalWeight = 0;
 
// All fruits
for (auto it = fruits.begin(); it != fruits.end(); ++it)
  totalWeight += it->getWeight();
 
// Apples (classic)
for (auto aIt = fruits[APPLE].begin(); aIt != fruits[APPLE].end(); ++aIt)
  std::cout << aIt->size() << std::endl;
```

Ici, en plus de pouvoir itérérer sur les sous conteneurs, il est possible d'itérer sur l'ensemble des objets de la `ComposedMap`.

La classe `ComposedMap` définit ses propres itérateurs qui prennent les valeurs présentées en bas du schéma qui suit.

![Working diagram](https://github.com/Manouel/Maps/blob/master/src/ComposedMap/working.png)

Si les sous-conteneurs sont des `map`, alors ce sont les valeurs des sous-maps qui seront retournées par les itérateurs.
