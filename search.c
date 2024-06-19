#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// typedef struct {
//     char name[100];
//     float rating;
//     float distance;
//     float travel_time;
// } Restaurant;

// Restaurant *restaurants = NULL;

typedef struct {
    char foodname[100];
    int fid;
} Fooditem;

char *rest_vocab[] = {
"mamagoto",
"paprika", "-", "courtyard", "by", "marriott",
"above", "sea", "level", "-", "the", "raintree",
"the", "reef", "-", "sheraton", "grand",
"punjab", "grill",
"soy", "soi",
"hamsa",
"bombay", "brasserie",
"azzuri", "bay",
"annalakshmi", "restaurant",
"savoury", "sea", "shell",
"the", "flying", "elephant", "-", "park", "hyatt",
"amelie's",
"little", "italy",
"ente", "keralam",
"sandy's", "chocolate", "laboratory",
"the", "fat", "boy",
"mkc", "-", "madras", "kitchen", "company",
"madras", "pavilion", "-", "itc", "grand", "chola",
"tuscana", "pizzeria",
"sigree",
"cream", "centre",
"junior", "kuppanna",
"brew", "room",
"upper", "deck", "-", "taj", "fisherman's", "cove", "resort", "&", "spa",
"sangeetha", "veg", "restaurant",
"pitcherr", "perfect",
"the", "alcove",
"flying", "elephant",
"grill", "wagon"};
int rest_vocab_size = sizeof(rest_vocab) / sizeof(rest_vocab[0]);

char *food_vocab[] = {
"sushi", "platter",
"thai", "green", "curry",
"japanese", "ramen",
"chicken", "teriyaki",
"asian", "stir-fried", "vegetables",
"tempura", "prawns",

"caesar", "salad",
"margherita", "pizza",
"grilled", "chicken",
"spaghetti", "bolognese",
"cheesecake",
"fresh", "lime", "soda",

"seafood", "platter",
"grilled", "fish",
"prawn", "cocktail",
"caesar", "salad",
"lemon", "tart",
"mojito",

"caesar", "salad",
"margherita", "pizza",
"grilled", "chicken",
"spaghetti", "bolognese",
"cheesecake",
"mojito",

"butter", "chicken",
"paneer", "tikka",
"dal", "makhani",
"garlic", "naan",
"gulab", "jamun",
"mango", "lassi",

"sushi", "platter",
"ramen",
"dim", "sum",
"pad", "thai",
"green", "tea", "ice", "cream",
"mango", "sticky", "rice",

"paneer", "tikka",
"dal", "makhani",
"vegetable", "biryani",
"butter", "naan",
"gajar", "ka", "halwa",
"mango", "lassi",

"paneer", "butter", "masala",
"chicken", "tikka",
"rogan", "josh",
"butter", "naan",
"lassi",
"gulab", "jamun",

"margherita", "pizza",
"pasta", "alfredo",
"caesar", "salad",
"grilled", "chicken",
"tiramisu",
"lemon", "iced", "tea",

"masala", "dosa",
"paneer", "butter", "masala",
"vegetable", "biryani",
"idli", "sambar",
"rasam", "rice",
"mango", "lassi",

"french", "onion", "soup",
"caesar", "salad",
"grilled", "chicken", "sandwich",
"classic", "cheeseburger",
"spaghetti", "carbonara",
"tiramisu",

"penne", "arrabbiata",
"margherita", "pizza",
"minestrone", "soup",
"tiramisu",
"bruschetta",
"gelato",

"malabar", "parotta",
"kerala", "fish", "curry",
"appam", "with", "stew",
"prawn", "mango", "curry",
"thalassery", "biryani",
"avial",

"dark", "chocolate", "cake",
"chocolate", "brownie",
"chocolate", "fondue",
"hot", "chocolate",
"chocolate", "milkshake",
"tiramisu",

"bbq", "ribs",
"buffalo", "wings",
"cheeseburger",
"loaded", "fries",
"chocolate", "milkshake",
"pulled", "pork", "sandwich",

"chicken", "chettinad",
"prawn", "moilee",
"malabar", "parotta",
"veg", "biryani",
"filter", "coffee",
"payasam",

"chettinad", "chicken",
"fish", "moilee",
"veg", "kurma",
"malabar", "parotta",
"appam",
"payasam",

"margherita", "pizza",
"quattro", "formaggi", "pizza",
"spaghetti", "aglio", "e", "olio",
"caesar", "salad",
"tiramisu",
"gelato",

"paneer", "tikka",
"chicken", "tandoori",
"dal", "makhani",
"naan",
"gajar", "halwa",
"mango", "lassi",

"channa", "bhatura",
"sizzling", "brownie",
"italian", "herbed", "cheese", "balls",
"american", "corn", "cheese", "balls",
"paneer", "tikka", "masala",
"mexican", "nachos",

"mutton", "biryani",
"chicken", "65",
"fish", "fry",
"egg", "kothu", "parotta",
"mutton", "sukka",
"curd", "rice",

"veg", "burger",
"chicken", "alfredo", "pasta",
"greek", "salad",
"waffles", "with", "maple", "syrup",
"espresso",
"lemon", "iced", "tea",

"rava", "dosa",
"veg", "biryani",
"onion", "uttapam",
"aloo", "paratha",
"gobi", "manchurian",
"mango", "lassi",

"margherita", "pizza",
"spaghetti", "carbonara",
"sushi", "platter",
"chicken", "caesar", "salad",
"tiramisu",
"chocolate", "milkshake",
"kung", "pao", "chicken",
"lemon", "iced", "tea",
"veg", "spring", "rolls",
"grilled", "chicken",
"garlic", "bread",
"cappuccino",

"chicken", "chettinad",
"masala", "dosa",
"fish", "curry",
"fried", "rice",
"veg", "hakka", "noodles",
"grilled", "sandwich",
"chicken", "burger",
"paneer", "tikka",
"chocolate", "brownie",
"lemonade",
"filter", "coffee",
"veg", "manchurian",

"butter", "chicken",
"paneer", "tikka",
"dal", "makhani",
"chicken", "fried", "rice",
"veg", "spring", "rolls",
"grilled", "fish",
"caesar", "salad",
"chocolate", "cake",
"brownie", "sundae",
"garlic", "naan",
"mango", "lassi",
"chicken", "noodles"
};
int food_vocab_size = sizeof(food_vocab) / sizeof(food_vocab[0]);

char *rest_array[] = {
    "above sea level - the raintree", 
    "amelie's", 
    "annalakshmi restaurant", 
    "azzuri bay", 
    "bombay brasserie", 
    "cream centre", 
    "ente keralam", 
    "grill wagon", 
    "hamsa", 
    "junior kuppanna", 
    "little italy", 
    "madras pavilion - itc grand chola", 
    "mamagoto", 
    "mkc - madras kitchen company", 
    "paprika - courtyard by marriott", 
    "pitcherr perfect", 
    "punjab grill", 
    "sandy's chocolate laboratory", 
    "sangeetha veg restaurant", 
    "savoury sea shell", 
    "sigree", 
    "soy soi", 
    "the alcove", 
    "the brew room", 
    "the fat boy", 
    "the flying elephant", 
    "the flying elephant - park hyatt", 
    "the reef - sheraton grand", 
    "tuscana pizzeria", 
    "upper deck - taj fisherman's cove resort & spa"
};
int rest_arr_size = sizeof(rest_array) / sizeof(rest_array[0]);

char *food_array[] = {
"sushi platter",
"thai green curry",
"japanese ramen",
"chicken teriyaki",
"asian stir-fried vegetables",
"tempura prawns",

"caesar salad",
"margherita pizza",
"grilled chicken",
"spaghetti bolognese",
"cheesecake",
"fresh lime soda",

"seafood platter",
"grilled fish",
"prawn cocktail",
"caesar salad",
"lemon tart",
"mojito",

"caesar salad",
"margherita pizza",
"grilled chicken",
"spaghetti bolognese",
"cheesecake",
"mojito",

"butter chicken",
"paneer tikka",
"dal makhani",
"garlic naan",
"gulab jamun",
"mango lassi",

"sushi platter",
"ramen",
"dim sum",
"pad thai",
"green tea ice cream",
"mango sticky rice",

"paneer tikka",
"dal makhani",
"vegetable biryani",
"butter naan",
"gajar ka halwa",
"mango lassi",

"paneer butter masala",
"chicken tikka",
"rogan josh",
"butter naan",
"lassi",
"gulab jamun",

"margherita pizza",
"pasta alfredo",
"caesar salad",
"grilled chicken",
"tiramisu",
"lemon iced tea",

"masala dosa",
"paneer butter masala",
"vegetable biryani",
"idli sambar",
"rasam rice",
"mango lassi",

"french onion soup",
"caesar salad",
"grilled chicken sandwich",
"classic cheeseburger",
"spaghetti carbonara",
"tiramisu",

"penne arrabbiata",
"margherita pizza",
"minestrone soup",
"tiramisu",
"bruschetta",
"gelato",

"malabar parotta",
"kerala fish curry",
"appam with stew",
"prawn mango curry",
"thalassery biryani",
"avial",

"dark chocolate cake",
"chocolate brownie",
"chocolate fondue",
"hot chocolate",
"chocolate milkshake",
"tiramisu",

"bbq ribs",
"buffalo wings",
"cheeseburger",
"loaded fries",
"chocolate milkshake",
"pulled pork sandwich",

"chicken chettinad",
"prawn moilee",
"malabar parotta",
"veg biryani",
"filter coffee",
"payasam",

"chettinad chicken",
"fish moilee",
"veg kurma",
"malabar parotta",
"appam",
"payasam",

"margherita pizza",
"quattro formaggi pizza",
"spaghetti aglio e olio",
"caesar salad",
"tiramisu",
"gelato",

"paneer tikka",
"chicken tandoori",
"dal makhani",
"naan",
"gajar halwa",
"mango lassi",

"channa bhatura",
"sizzling brownie",
"italian herbed cheese balls",
"american corn cheese balls",
"paneer tikka masala",
"mexican nachos",

"mutton biryani",
"chicken 65",
"fish fry",
"egg kothu parotta",
"mutton sukka",
"curd rice",

"veg burger",
"chicken alfredo pasta",
"greek salad",
"waffles with maple syrup",
"espresso",
"lemon iced tea",

"rava dosa",
"veg biryani",
"onion uttapam",
"aloo paratha",
"gobi manchurian",
"mango lassi",

"margherita pizza",
"spaghetti carbonara",
"sushi platter",
"chicken caesar salad",
"tiramisu",
"chocolate milkshake",
"kung pao chicken",
"lemon iced tea",
"veg spring rolls",
"grilled chicken",
"garlic bread",
"cappuccino",

"chicken chettinad",
"masala dosa",
"fish curry",
"fried rice",
"veg hakka noodles",
"grilled sandwich",
"chicken burger",
"paneer tikka",
"chocolate brownie",
"lemonade",
"filter coffee",
"veg manchurian",

"butter chicken",
"paneer tikka",
"dal makhani",
"chicken fried rice",
"veg spring rolls",
"grilled fish",
"caesar salad",
"chocolate cake",
"brownie sundae",
"garlic naan",
"mango lassi",
"chicken noodles"
};
int food_arr_size = sizeof(food_array) / sizeof(food_array[0]);

Fooditem fooditems_array[] = {
        {"Seafood Platter", 101},
        {"Grilled Fish", 102},
        {"Prawn Cocktail", 103},
        {"Caesar Salad", 104},
        {"Lemon Tart", 105},
        {"Mojito", 106},
        {"French Onion Soup", 201},
        {"Caesar Salad", 202},
        {"Grilled Chicken Sandwich", 203},
        {"Classic Cheeseburger", 204},
        {"Spaghetti Carbonara", 205},
        {"Tiramisu", 206},
        {"Masala Dosa", 301},
        {"Paneer Butter Masala", 302},
        {"Vegetable Biryani", 303},
        {"Idli Sambar", 304},
        {"Rasam Rice", 305},
        {"Mango Lassi", 306},
        {"Margherita Pizza", 401},
        {"Pasta Alfredo", 402},
        {"Caesar Salad", 403},
        {"Grilled Chicken", 404},
        {"Tiramisu", 405},
        {"Lemon Iced Tea", 406},
        {"Paneer Butter Masala", 501},
        {"Chicken Tikka", 502},
        {"Rogan Josh", 503},
        {"Butter Naan", 504},
        {"Lassi", 505},
        {"Gulab Jamun", 506},
        {"Channa Bhatura", 601},
        {"Sizzling Brownie", 602},
        {"Italian Herbed Cheese Balls", 603},
        {"American Corn Cheese Balls", 604},
        {"Paneer Tikka Masala", 605},
        {"Mexican Nachos", 606},
        {"Malabar Parotta", 701},
        {"Kerala Fish Curry", 702},
        {"Appam with Stew", 703},
        {"Prawn Mango Curry", 704},
        {"Thalassery Biryani", 705},
        {"Avial", 706},
        {"Butter Chicken", 801},
        {"Paneer Tikka", 802},
        {"Dal Makhani", 803},
        {"Chicken Fried Rice", 804},
        {"Veg Spring Rolls", 805},
        {"Grilled Fish", 806},
        {"Caesar Salad", 807},
        {"Chocolate Cake", 808},
        {"Brownie Sundae", 809},
        {"Garlic Naan", 810},
        {"Mango Lassi", 811},
        {"Chicken Noodles", 812},
        {"Butter Chicken", 901},
        {"Paneer Tikka", 902},
        {"Dal Makhani", 903},
        {"Chicken Fried Rice", 904},
        {"Veg Spring Rolls", 905},
        {"Grilled Fish", 906},
        {"Caesar Salad", 907},
        {"Chocolate Cake", 908},
        {"Brownie Sundae", 909},
        {"Butter Chicken", 1001},
        {"Dal Makhani", 1002},
        {"Vegetable Biryani", 1003},
        {"Butter Naan", 1004},
        {"Gajar Ka Halwa", 1005},
        {"Mango Lassi", 1006},
        {"Penne Arrabbiata", 1101},
        {"Margherita Pizza", 1102},
        {"Minestrone Soup", 1103},
        {"Tiramisu", 1104},
        {"Bruschetta", 1105},
        {"Gelato", 1106},
        {"Chettinad Chicken", 1201},
        {"Fish Moilee", 1202},
        {"Veg Kurma", 1203},
        {"Malabar Parotta", 1204},
        {"Appam", 1205},
        {"Payasam", 1206},
        {"Sushi Platter", 1301},
        {"Thai Green Curry", 1302},
        {"Japanese Ramen", 1303},
        {"Chicken Teriyaki", 1304},
        {"Asian Stir-Fried Vegetables", 1305},
        {"Tempura Prawns", 1306},
        {"Chicken Chettinad", 1401},
        {"Prawn Moilee", 1402},
        {"Malabar Parotta", 1403},
        {"Veg Biryani", 1404},
        {"Filter Coffee", 1405},
        {"Payasam", 1406},
        {"Caesar Salad", 1501},
        {"Margherita Pizza", 1502},
        {"Grilled Chicken", 1503},
        {"Spaghetti Bolognese", 1504},
        {"Cheesecake", 1505},
        {"Fresh Lime Soda", 1506},
        {"Salted Lemon Fish", 1507},
        {"Margherita Pizza", 1601},
        {"Spaghetti Carbonara", 1602},
        {"Sushi Platter", 1603},
        {"Chicken Caesar Salad", 1604},
        {"Tiramisu", 1605},
        {"Chocolate Milkshake", 1606},
        {"Kung Pao Chicken", 1607},
        {"Lemon Iced Tea", 1608},
        {"Veg Spring Rolls", 1609},
        {"Grilled Chicken", 1610},
        {"Garlic Bread", 1611},
        {"Cappuccino", 1612},
        {"Butter Chicken", 1701},
        {"Paneer Tikka", 1702},
        {"Dal Makhani", 1703},
        {"Garlic Naan", 1704},
        {"Gulab Jamun", 1705},
        {"Mango Lassi", 1706},
        {"Dark Chocolate Cake", 1801},
        {"Chocolate Brownie", 1802},
        {"Chocolate Fondue", 1803},
        {"Hot Chocolate", 1804},
        {"Chocolate Milkshake", 1805},
        {"Tiramisu", 1806},
        {"Rava Dosa", 1901},
        {"Veg Biryani", 1902},
        {"Onion Uttapam", 1903},
        {"Aloo Paratha", 1904},
        {"Gobi Manchurian", 1905},
        {"Mango Lassi", 1906},
        {"Grilled Prawns", 2001},
        {"Fish Curry", 2002},
        {"Chicken Tikka", 2003},
        {"Mutton Biryani", 2004},
        {"Paneer Butter Masala", 2005},
        {"Lassi", 2006},
        {"Paneer Tikka", 2101},
        {"Chicken Tandoori", 2102},
        {"Dal Makhani", 2103},
        {"Naan", 2104},
        {"Gajar Halwa", 2105},
        {"Mango Lassi", 2106},
        {"Sushi Platter", 2201},
        {"Ramen", 2202},
        {"Dim Sum", 2203},
        {"Pad Thai", 2204},
        {"Green Tea Ice Cream", 2205},
        {"Mango Sticky Rice", 2206},
        {"Chicken Chettinad", 2301},
        {"Masala Dosa", 2302},
        {"Fish Curry", 2303},
        {"Fried Rice", 2304},
        {"Veg Hakka Noodles", 2305},
        {"Grilled Sandwich", 2306},
        {"Chicken Burger", 2307},
        {"Paneer Tikka", 2308},
        {"Chocolate Brownie", 2309},
        {"Lemonade", 2310},
        {"Filter Coffee", 2311},
        {"Veg Manchurian", 2312},
        {"Veg Burger", 2401},
        {"Chicken Alfredo Pasta", 2402},
        {"Greek Salad", 2403},
        {"Waffles with Maple Syrup", 2404},
        {"Espresso", 2405},
        {"Lemon Iced Tea", 2406},
        {"BBQ Ribs", 2501},
        {"Buffalo Wings", 2502},
        {"Cheeseburger", 2503},
        {"Loaded Fries", 2504},
        {"Chocolate Milkshake", 2505},
        {"Pulled Pork Sandwich", 2506},
        {"BBQ Pork Ribs", 2601},
        {"Grilled Lamb Chops", 2602},
        {"Caesar Salad", 2603},
        {"Margherita Pizza", 2604},
        {"Chocolate Fondant", 2605},
        {"Mango Smoothie", 2606},
        {"Caesar Salad", 2701},
        {"Margherita Pizza", 2702},
        {"Grilled Chicken", 2703},
        {"Spaghetti Bolognese", 2704},
        {"Cheesecake", 2705},
        {"Mojito", 2706},
        {"Margherita Pizza", 2801},
        {"Quattro Formaggi Pizza", 2802},
        {"Spaghetti Aglio e Olio", 2803},
        {"Caesar Salad", 2804},
        {"Tiramisu", 2805},
        {"Gelato", 2806},
        {"Grilled Fish", 2901},
        {"Caesar Salad", 2902},
        {"Lamb Chops", 2903},
        {"Chicken Skewers", 2904},
        {"Tiramisu", 2905},
        {"Mojito", 2906},
    };
int fooditems_array_size = sizeof(fooditems_array) / sizeof(fooditems_array[0]);

void strip_endspaces(char *str) {
    int len = strlen(str);
    int i;

    // Traverse from the end of the string towards the beginning
    for (i = len - 1; i >= 0; i--) {
        if (!isspace(str[i])) {
            break;
        }
    }

    // Null-terminate the string at the first non-space character from the end
    str[i + 1] = '\0';
}

void tokenize_and_vectorize(const char *str, int *vector, char **vocabulary, int vocab_size) {
    char *temp_str = strdup(str);
    char *token = strtok(temp_str, " ");
    while (token != NULL) {
        for (int i = 0; i < vocab_size; i++) {
            if (strcmp(token, vocabulary[i]) == 0) {
                vector[i]++;
                break;
            }
        }
        token = strtok(NULL, " ");
    }
    free(temp_str);
}


double cosine_similarity(int *vec1, int *vec2, int size) {
    double dot_product = 0.0, norm_a = 0.0, norm_b = 0.0;
    for (int i = 0; i < size; i++) {
        dot_product += vec1[i] * vec2[i];
        norm_a += vec1[i] * vec1[i];
        norm_b += vec2[i] * vec2[i];
    }
    return dot_product / (sqrt(norm_a) * sqrt(norm_b));
}

char* find_most_similar_string(char **array, int array_size, const char *search_string, char **vocabulary, int vocab_size) {
    int search_vector[vocab_size];
    memset(search_vector, 0, sizeof(search_vector));

    tokenize_and_vectorize(search_string, search_vector, vocabulary, vocab_size);

    double max_similarity = -1.0;
    int best_match_index = -1;

    for (int i = 0; i < array_size; i++) {
        int array_vector[vocab_size];
        memset(array_vector, 0, sizeof(array_vector));
        tokenize_and_vectorize(array[i], array_vector, vocabulary, vocab_size);

        double similarity = cosine_similarity(search_vector, array_vector, vocab_size);
        if (similarity > max_similarity) {
            max_similarity = similarity;
            best_match_index = i;
        }
    }

    // Check if a match was found
    if (best_match_index == -1) {
        return NULL;
    }

    return array[best_match_index];
}

char *search_food1(char *search_string) {
    char *most_similar = find_most_similar_string(food_array, food_arr_size, search_string, food_vocab, food_vocab_size);
    if (most_similar != NULL) {
        return most_similar;
    } else {
        return NULL;
    }
}

void search_rest1(char *search_string) {
    char *most_similar = find_most_similar_string(rest_array, rest_arr_size, search_string, rest_vocab, rest_vocab_size);
    if (most_similar != NULL) {
        printf("Similar Food: %s\n", most_similar);
    } else {
        printf("No similar food found.\n");
    }
}

void find_top_n_similar_strings(char **array, int array_size, const char *search_string, char **vocabulary, int vocab_size, char **top_n, int n) {
    int search_vector[vocab_size];
    memset(search_vector, 0, sizeof(search_vector));

    tokenize_and_vectorize(search_string, search_vector, vocabulary, vocab_size);

    double max_similarity[n];
    int best_match_indices[n];

    for (int i = 0; i < n; i++) {
        max_similarity[i] = -1.0;
        best_match_indices[i] = -1;
    }

    for (int i = 0; i < array_size; i++) {
        int array_vector[vocab_size];
        memset(array_vector, 0, sizeof(array_vector));
        tokenize_and_vectorize(array[i], array_vector, vocabulary, vocab_size);

        double similarity = cosine_similarity(search_vector, array_vector, vocab_size);

        // Check if this similarity should be in the top n
        for (int j = 0; j < n; j++) {
            if (similarity > max_similarity[j]) {
                // Shift lower similarities down
                for (int k = n - 1; k > j; k--) {
                    max_similarity[k] = max_similarity[k - 1];
                    best_match_indices[k] = best_match_indices[k - 1];
                }
                // Insert new similarity
                max_similarity[j] = similarity;
                best_match_indices[j] = i;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (best_match_indices[i] != -1) {
            top_n[i] = array[best_match_indices[i]];
        } else {
            top_n[i] = NULL;
        }
    }
}
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

char* get_restaurant_name(int food_id) {
    // Extract the index from the food ID
    int index = (food_id % 100) - 1;

    // Check if the index is valid
    if (food_id==-1) return NULL;
    if (index < 0 || index >= rest_arr_size) {
        return "Invalid food ID";
    }

    // Return the restaurant name
    return rest_array[index];
}

int get_food_id(char *recommfoodname){
    char temp[40];
    for (int i=0; i<fooditems_array_size; i++){
        strcpy(temp, fooditems_array[i].foodname);
        to_lowercase(temp);
        printf("%s. %s.\n", recommfoodname, temp);
        if (strcmp(recommfoodname, temp)==0){
            return fooditems_array[i].fid;
        }
    }
    return -1;
}

char *getfoodname(int fid){
    for (int i=0; i<fooditems_array_size; i++){
        if (fid == fooditems_array[i].fid){
            return fooditems_array[i].foodname;
        }
    }
}

// Search food function
Fooditem* search_food(const char *search_string) {
    char *top_3[3] = {NULL, NULL, NULL};
    find_top_n_similar_strings(food_array, food_arr_size, search_string, food_vocab, food_vocab_size, top_3, 3);

    Fooditem *result = (Fooditem *)malloc(3 * sizeof(Fooditem));
    if (result == NULL) {
        perror("Failed to allocate memory for food search result");
        return NULL;
    }

    for (int i = 0; i < 3; i++) {
        if (top_3[i] != NULL) {
            strncpy(result[i].foodname, top_3[i], sizeof(result[i].foodname) - 1);
            result[i].foodname[sizeof(result[i].foodname) - 1] = '\0'; // Ensure null-termination
            
            // Find the fid corresponding to the foodname
            result[i].fid = -1; // Initialize fid to -1 in case no match is found
            for (int j = 0; j < fooditems_array_size; j++) {
                if (strcmp(result[i].foodname, fooditems_array[j].foodname) == 0) {
                    result[i].fid = fooditems_array[j].fid;
                    break; // Exit loop once fid is found
                }
            }
        } else {
            // Handle case when no similar strings are found
            result[i].foodname[0] = '\0'; // Empty string
            result[i].fid = -1; // Invalid fid
        }
    }

    return result;
}


// Search restaurant function
char **search_rest(const char *search_string) {
    char *top_3[3] = {NULL, NULL, NULL};
    find_top_n_similar_strings(rest_array, rest_arr_size, search_string, rest_vocab, rest_vocab_size, top_3, 3);

    char **result = (char **)malloc(3 * sizeof(char *));
    if (result == NULL) {
        perror("Failed to allocate memory for restaurant search result");
        return NULL;
    }

    for (int i = 0; i < 3; i++) {
        if (top_3[i] != NULL) {
            result[i] = (char *)malloc((strlen(top_3[i]) + 1) * sizeof(char));
            if (result[i] == NULL) {
                perror("Failed to allocate memory for result[i]");
                // Free previously allocated memory
                for (int j = 0; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strcpy(result[i], top_3[i]);
        } else {
            result[i] = NULL;
        }
    }

    return result;
}

void free_search_result(char **result) {
    if (result != NULL) {
        for (int i = 0; i < 3; i++) {
            if (result[i] != NULL) {
                free(result[i]);
            }
        }
        free(result);
    }
}
char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}
int find_restaurant(Restaurant *restaurants, int size, char *rest_n, Restaurant *result) {
    char lower_rest_n[100];
    char lower_rest_name[100];

    // Convert rest_n to lowercase
    strcpy(lower_rest_n, rest_n);
    to_lowercase(lower_rest_n);

    for (int i = 0; i < size; i++) {
        strcpy(lower_rest_name, restaurants[i].name);

        // Convert restaurant name to lowercase
        to_lowercase(lower_rest_name);
        strip_endspaces(lower_rest_name);
        printf("%s. %s.\n", lower_rest_n, lower_rest_name);

        if (strcmp(lower_rest_n, lower_rest_name) == 0) {
            // Copy the restaurant details to the result
            *result = restaurants[i];
            return 1;  // Return 1 if match is found
        }
    }
    return 0;  // Return 0 if no match is found
}
Restaurant *get_matched_rnames_food(Restaurant *restaurants, int n_rest, Fooditem *results) {
    Restaurant *matched = (Restaurant *)malloc(3 * sizeof(Restaurant));
    if (matched == NULL) {
        perror("Failed to allocate memory for matched restaurants");
        return NULL;
    }

    for (int i = 0; i < 3; i++) {
        matched[i].name[0] = '\0';
    }
    char restname[100];
    for (int i = 0; i < 3; i++) {
        if (results[i].foodname != NULL) {
            for (int j = 0; j < n_rest; j++) {
                strip_endspaces(restaurants[j].name);
                toLower(restaurants[j].name);
                sscanf(get_restaurant_name(results[i].fid), "%[^\n]", restname);
                printf("%s %s\n", restname, restaurants[j].name);
                if (strcmp(restname, restaurants[j].name) == 0) {
                    strncpy(matched[i].name, restaurants[j].name, sizeof(matched[i].name) - 1);
                    matched[i].name[sizeof(matched[i].name) - 1] = '\0';  // Ensure null-termination
                    matched[i].rating = restaurants[j].rating;
                    matched[i].distance = restaurants[j].distance;
                    matched[i].travel_time = restaurants[j].travel_time;
                    break;
                }
            }
        }
    }

    return matched;
}

Restaurant* get_matched_restaurant_names(Restaurant *restaurants, int n_rest, const char *search_string) {
    // Dynamically allocate memory for matched restaurants
    Restaurant *matched = (Restaurant *)malloc(3 * sizeof(Restaurant));
    if (matched == NULL) {
        perror("Failed to allocate memory for matched restaurants");
        return NULL;
    }

    // Initialize the names in matched restaurants to empty strings
    for (int i = 0; i < 3; i++) {
        matched[i].name[0] = '\0';
    }

    char **results = search_rest(search_string);
    if (results == NULL) {
        free(matched);
        return NULL;
    }

    for (int i = 0; i < 3; i++) {
        if (results[i] != NULL) {
            for (int j = 0; j < n_rest; j++) {
                strip_endspaces(restaurants[j].name);
                toLower(restaurants[j].name);
                if (strcmp(results[i], restaurants[j].name) == 0) {
                    strncpy(matched[i].name, restaurants[j].name, sizeof(matched[i].name) - 1);
                    matched[i].name[sizeof(matched[i].name) - 1] = '\0';  // Ensure null-termination
                    matched[i].rating = restaurants[j].rating;
                    matched[i].distance = restaurants[j].distance;
                    matched[i].travel_time = restaurants[j].travel_time;
                    break;
                }
            }
        }
    }

    // Free the search_rest result
    free_search_result(results);

    return matched;
}