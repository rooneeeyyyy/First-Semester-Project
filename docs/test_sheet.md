# Test Sheet

Run the program from the project root. Fill the last column with Pass or Fail.

## Startup
| # | Test | Expected | Pass/Fail |
|---|---|---|---|
| 1 | Start the program | `Loaded: 14 locations, 22 routes, 8 food items, 4 cafeterias` | | 
| 2 | Rename data/food.csv, start the program, then rename it back | `Error: cannot open data/food.csv`, the "required data could not be loaded" message, and the program exits | |
| 3 | Add the line `9,Bad Item,Snacks,abc,1` to food.csv, start, then delete the line | `Warning: data/food.csv line 10 skipped (bad row)` and 8 food items | |
| 4 | Main menu: type `x`, then `9` | Invalid choice message each time, and the menu returns | |

## Food
| # | Test | Expected | Pass/Fail |
|---|---|---|---|
| 5 | Food > Search: `biryani` | 2 rows (IDs 1 and 8) | |
| 6 | Food > Search: `SNACKS` | 3 rows | |
| 7 | Food > Search: `  tea  ` | 1 row (Test Tea) | |
| 8 | Food > Search: `pizza` | `No matching food found.` | |
| 9 | Food > Search: empty line | `Search cannot be empty.` | |
| 10 | Food > Budget: `50`, empty category | 1 row (Test Samosa, price exactly 50) | |
| 11 | Food > Budget: `49`, empty category | `No items found within this budget.` | |
| 12 | Food > Budget: `abc` | `Budget must be a whole number above 0.` | |
| 13 | Food > Budget: `100`, category `drinks` | 2 rows | |

## Cafeterias
| # | Test | Expected | Pass/Fail |
|---|---|---|---|
| 14 | Cafeterias > List | 4 cafeterias, each with hours 08:00-16:00 | |
| 15 | View cafeteria `3` | Tasty Canteen, Academic Block 2, opening hours, 2 menu rows | |
| 16 | View cafeteria `4` | Juice Center and `No items listed.` | |
| 17 | View cafeteria `9` | `Cafeteria not found.` | |
| 18 | View cafeteria `abc` | `Invalid cafeteria ID.` | |
| 19 | Compare `1 2` | Table of 5 items, Test Biryani 250 and 270, `-` where an item is not sold | |
| 20 | Compare `1` | `Enter at least two cafeteria IDs.` | |
| 21 | Compare `1 2 3 1` | `You can compare at most three cafeterias.` | |
| 22 | Compare `2 2` | `Each cafeteria can be chosen only once.` | |
| 23 | Compare `1 9` | `Cafeteria 9 not found.` | |

## Campus map and routes
| # | Test | Expected | Pass/Fail |
|---|---|---|---|
| 24 | Map > Show all locations | 14 locations | |
| 25 | Map > Show connections | 22 connections | |
| 26 | Map > Search: `library` | `Matched: Library and Cafe` then `Found: ID 9 - Library and Cafe` | |
| 27 | Map > Search: `gate` | `Several places match 'gate':` with 4 names | |
| 28 | Map > Search: `Hostel` | `Location not found.` | |
| 29 | Route: `Main Gate` to `Mosque` | Main Gate, Academic Block 1, Mosque, 2 connections, 110 m | |
| 30 | Route: `Parking Area` to `Gate 4` | Parking Area, Main Gate, Academic Block 1, Academic Block 3, Gate 4, 4 connections, 250 m | |
| 31 | Route: `Gate 2` to `Mosque` | 3 connections, 180 m | |
| 32 | Route: `Mosque` to `Mosque` | `You are already at Mosque.` | |
| 33 | Route: `Library` to `Hostel` | `Destination not found.` | |
| 34 | Add the line `15,Island` to locations.csv, route `Main Gate` to `Island`, then delete the line | `No route found between Main Gate and Island.` | |
| 35 | Route: `library` to `gym` | Both names matched, 1 connection, 35 m | |

## Assistant
| # | Test | Expected | Pass/Fail |
|---|---|---|---|
| 36 | `hello` | `Understood: unknown request` and the fallback message | |
| 37 | `help` | `Understood: help` and the list of examples | |
| 38 | `biryani price` | price search, 2 rows | |
| 39 | `food under 150` | price search, 4 rows | |
| 40 | `cheap food` | `Cheap means Rs. 100 or less.` and 3 rows | |
| 41 | `show cafeterias` | the list of 4 cafeterias | |
| 42 | `badr canteen menu` | Badr Canteen, Mosque, 3 menu rows | |
| 43 | `where is the library` | `Found: ID 9 - Library and Cafe` and its connections | |
| 44 | `route from Main Gate to Mosque` | 110 m route | |
| 45 | `biryani kahan milegi` (Roman Urdu) | food search, 2 rows | |
| 46 | `sasta khana` (Roman Urdu) | cheap search, 3 rows | |
| 47 | `biryani kitne ka hai` (Roman Urdu) | price search, 2 rows | |
| 48 | `mosque qareeb kya hai` (Roman Urdu) | Mosque and its 3 connections | |
| 49 | `main gate se library tak` (Roman Urdu) | route of 95 m | |
| 50 | empty line | `Please type a question. Type 'help' for examples.` | |

## Favorites
| # | Test | Expected | Pass/Fail |
|---|---|---|---|
| 51 | Favorites > Add > Food > `3` | `Added to favorites.` | |
| 52 | Add the same item again | `Already in your favorites.` | |
| 53 | Add Food `99` | `That ID does not exist.` | |
| 54 | Add type `7` | `Invalid type. Enter 1, 2 or 3.` | |
| 55 | Add with ID `abc` | `Invalid ID.` | |
| 56 | Show favorites | The added items with names (food shows the price) | |
| 57 | Exit the program, start it again, show favorites | The same items are still there | |
| 58 | Remove Food `3` | `Removed from favorites.` | |
| 59 | Remove Food `3` again | `That item is not in your favorites.` | |
