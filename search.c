#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
"mamagoto", "paprika - courtyard by marriott", "above sea level - the raintree", "the reef - sheraton grand", "punjab grill", "soy soi", "hamsa", "bombay brasserie", "azzuri bay", "annalakshmi restaurant", "savoury sea shell", "the flying elephant - park hyatt", "amelie's", "little italy", "ente keralam", "sandy's chocolate laboratory", "the fat boy", "mkc - madras kitchen company", "madras pavilion - itc grand chola", "tuscana pizzeria", "sigree", "cream centre", "junior kuppanna", "the brew room", "upper deck - taj fisherman's cove resort & spa", "sangeetha veg restaurant", "pitcherr perfect", "the alcove", "grill wagon", "the flying elephant"
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

void search_food(char *search_string) {
    char *most_similar = find_most_similar_string(food_array, food_arr_size, search_string, food_vocab, food_vocab_size);
    if (most_similar != NULL) {
        printf("Related Restaurants: %s\n", most_similar);
    } else {
        printf("No similar restaurants found.\n");
    }
}

void search_rest(char *search_string) {
    char *most_similar = find_most_similar_string(rest_array, rest_arr_size, search_string, rest_vocab, rest_vocab_size);
    if (most_similar != NULL) {
        printf("Similar Food: %s\n", most_similar);
    } else {
        printf("No similar food found.\n");
    }
}
