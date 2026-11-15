# Data Fields

All files are plain text with one record per line, the first line is a header, and fields are separated by commas. Fields must not contain commas.

## data/locations.csv
id,name
- id: whole number, starting at 1 and increasing by 1 with no gaps
- name: text shorter than 30 characters

## data/routes.csv
from_id,to_id,distance
- from_id, to_id: IDs that exist in locations.csv, and they must be different
- distance: positive whole number in metres (estimated, not measured)
- A route works in both directions

## data/food.csv
food_id,name,category,price,vendor_id
- food_id: unique positive whole number
- name: shorter than 30 characters, category: shorter than 20 characters
- price: positive whole number in PKR
- vendor_id: the vendor_id of a cafeteria

## data/cafeterias.csv
vendor_id,name,location_id,opening_hours
- vendor_id: unique positive whole number
- location_id: an ID that exists in locations.csv
- opening_hours: text shorter than 20 characters, for example 08:00-16:00

## data/favorites.txt (created by the program)
type,id
- type: food, cafeteria or location
- id: the ID of that item

## Missing and bad data
- A missing required file stops the program with a clear message.
- A bad row is skipped and the program prints a warning with the file name and line number.
- A favorite whose item no longer exists is skipped with a warning when the file is loaded.
