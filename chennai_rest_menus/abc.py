import os

# List of restaurant file names
restaurant_files = [
    "Mamagoto", "Paprika - Courtyard by Marriott", "Above Sea Level - The Raintree", 
    "The Reef - Sheraton Grand", "Punjab Grill", "Soy Soi", "Hamsa", "Bombay Brasserie", 
    "Azzuri Bay", "Annalakshmi Restaurant", "Savoury Sea Shell", "The Flying Elephant - Park Hyatt", 
    "Amelie's", "Little Italy", "Ente Keralam", "Sandy's Chocolate Laboratory", "The Fat Boy", 
    "MKC - Madras Kitchen Company", "Madras Pavilion - ITC Grand Chola", "Tuscana Pizzeria", 
    "Sigree", "Cream Centre", "Junior Kuppanna", "The Brew Room", 
    "Upper Deck - Taj Fisherman's Cove Resort & Spa", "Sangeetha Veg Restaurant", 
    "Pitcherr Perfect", "The Alcove", "Grill Wagon"
]

# Initialize an empty list to store the dish names
dish_names = []

# Walk through each restaurant file and extract dish names
for restaurant in restaurant_files:
    file_name = f"chennai_rest_menus/{restaurant}.txt"
    if os.path.isfile(file_name):
        with open(file_name, 'r', encoding='utf-8') as file:
            for line in file:
                parts = line.strip().split(', ')
                if len(parts) >= 2:
                    dish_names.append(parts[1])

# Write the list of dish names to a new file
output_file = "dish_names.txt"
with open(output_file, 'w', encoding='utf-8') as file:
    for dish_name in dish_names:
        file.write(dish_name + '\n')

print(f"Extracted {len(dish_names)} dish names and wrote them to {output_file}.")
