#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include <cstdlib>
#include<list>
#include <unordered_set>
#include "../../jjsson/single_include/nlohmann/json.hpp"
using json = nlohmann::json; // Alias for nlohmann::json
json actualjson; // Global variable to store JSON data

using namespace std;
    void login();
    void signin();
    void tittle();
    void secondpage();
    void update();
    void secondpage1();
    void foodlist();
    void foodchoice(string);
    void lastpage();




// Function to convert JSON value to string without quotation marks
string toStringWithoutQuotes(const json& j)
{
    if (j.is_string()) {
        return j.get<string>();
    } else {
        return "";
    }
}

void forjson() {
    // Open the input file
    ifstream file("food.json");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    // Parse the JSON
    try {
        file >> actualjson;
    } catch (const json::parse_error& e) {
        cerr << "Parse error: " << e.what() << endl;
        return;
    }
}


void displayRandomFood(const json& actualjson)
{
    string food;
   // Get the array of food items
    const json& foods = actualjson["foods"];

    // Get the total number of food items
    int totalFoods = foods.size();

    // Generate a random index within the range of the food items
    int randomFoodIndex = rand() % totalFoods;

    // Get the randomly selected food item
    const json& randomFood = foods[randomFoodIndex];

    // Display the selected food item

            food=toStringWithoutQuotes(randomFood["name"]);
            cout << "\nRandomly Selected Food:" << food<< endl;
            cout<<"Enter to continue:";
            cin.ignore(); // Ignore any previous newline character
            cin.get();

            foodchoice(food);



}
void displayRandomRestaurant(const json& jsonData, const string& foodName) {
    // Get the array of food items
    const json& foods = jsonData["foods"];

    // Search for the given food item
    for (const auto& food : foods) {
        if (toStringWithoutQuotes(food["name"]) == foodName) {
            // Get the array of restaurants for the selected food item
            const json& restaurants = food["restaurants"];

            // Get the total number of restaurants for the selected food item
            int totalRestaurants = restaurants.size();

            // Generate a random index within the range of restaurants
            int randomRestaurantIndex = rand() % totalRestaurants;

            // Display randomly selected restaurant and its rating
            system("cls");
            tittle();
            cout << "\t\t\tRandomly selected restaurant for " << foodName << ":" << endl<<endl;
            cout << "\t\t\tRestaurant: " << toStringWithoutQuotes(restaurants[randomRestaurantIndex]["name"]) << endl;
            cout << "\t\t\tRating: " << restaurants[randomRestaurantIndex]["rating"] << endl;

            return; // Exit after displaying one restaurant
        }
    }

    // If the given food item is not found
    cout << "Food item not found: " << foodName << endl;
    lastpage();
}
int main()
{
    forjson();
    int option;
    do
    {
    tittle();
    cout << "\t\t\t1. Sign up\n \t\t\t2. Login\n \t\t\t3. Exit\n";
    cout << "\t\t\t--------------------------------------" << endl;
    cout << "\t\t\t\t choice:[1/2/3]" << endl;
    cout << "\t\t\t--------------------------------------" << endl;
    cout << "enter your choice:";
    cin >> option;
    switch(option)
    {
        case 1:
            signin();
            break;
        case 2:
            login();
            break;
        case 3:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            main();
    }
    }while(option==1);
    return 0;

}

void tittle()
{
    cout << "\t\t\t--------------------------------------" << endl;
    cout << "\t\t\t\t |ShuffleNeat|" << endl;
    cout << "\t\t\t--------------------------------------" << endl;
}
//for registration
void signin()
{
    string reguser,regpass,ru,pu;
    system("cls");
    cout << "\t\t\t--------------------------------------" << endl;
    cout << "\t\t\t\t\t|SIGN UP|" << endl;
    cout << "\t\t\t--------------------------------------" << endl;
    cout << "\t\t\tNew username: ";
    cin >> reguser;
    cout << "\t\t\tPassword: ";
    cin >> regpass;

    ofstream reg("database.txt",ios::app);
    reg<<reguser<<" "<<regpass<<endl;
    system("cls");
    cout<<"\nRegistration Successful"<<endl;

}

void login()
{
    int count;
    string user,pass,u,p;
    system("cls");
    cout << "\t\t\t--------------------------------------" << endl;
    cout << "\t\t\t\t\t|LOGIN PAGE|" << endl;
    cout << "\t\t\t--------------------------------------" << endl;
    cout << "\t\t\tUsername: ";
    cin >> user;
    cout << "\t\t\tPassword: ";
    cin >> pass;
    ifstream input("database.txt");
    while(input>>u>>p)
    {
        if(u==user && p==pass)
        {
            count=1;
            system("cls");
        }
    }
    input.close();
    if(count==1)
    {
        tittle();
        cout<<"\t\t\t\t  WELCOME!!, "<<user<<endl;
        cin.get();
        secondpage();
    }
    else
    {
        cout<<"\nLOGIN ERROR!!\nPlease check your username and password"<<endl;
    }
}
void secondpage()
{
    int b;
    cout<<"\t\t\tHow can I help Today?"<<endl;
    cout<<"\t\t\t 1.Main page"<<endl;
    cout<<"\t\t\t 2.Found a gem(update)"<<endl;
    cout<<"\nEnter your choice:";
    cin>>b;
  switch(b)
    {
            case 1:
                secondpage1();
                break;
            case 2:
                  update();
                break;
            default:
                 cout << "Invalid choice. Please try again.\n";
                secondpage();
    }
}

void update()
 {
    string dish, place;
    float rating;
    system("cls");
    tittle();
    cout << "\n\t\t\t Please enter your personal found Gem info " << endl;

    // Get dish and place from the user
    cout << "\t\t\t Dish you liked : ";
    cin >> dish;
    cout << "\t\t\t Place name : ";
    cin >> place;
    cout << "\t\t\t Your rating : ";
    cin >> rating;
    cout << fixed << setprecision(2);


    // Load existing JSON data from file
    forjson();


    // Check if the dish already exists in the JSON data
    bool dishExists = false;
    for (auto& foodItem : actualjson["foods"])
    {
        if (toStringWithoutQuotes(foodItem["name"]) == dish)
        {
            // Get the size of the "restaurants" array
            int restaurantsSize = foodItem["restaurants"].size();
            // Update place and rating for the existing dish
            foodItem["restaurants"][restaurantsSize]["name"] = place;
            foodItem["restaurants"][restaurantsSize]["rating"] = rating;
            dishExists = true;
            break;
        }
    }

    // If dish does not exist, add it to JSON data
    if (!dishExists)

    {
        json newRestaurant;
        newRestaurant["name"] = place;
        newRestaurant["rating"] = rating;
        json newFoodItem;
        newFoodItem["name"] = dish;
        newFoodItem["restaurants"] = json::array({newRestaurant});
        actualjson["foods"].push_back(newFoodItem);

    }

    // Write JSON back to original file
    ofstream outFile("food.json");
    if (outFile.is_open())
    {
        outFile << actualjson.dump(4); // Pretty print with 4 spaces indentation
        outFile.close();
        cout << "\n\n\t\t\t Your Gem information has been successfully added!!" << endl;
    }
    else
     {
        cerr << "Unable to open file for writing!" << endl;
    }


}
void secondpage1()
{
    system("cls");
    tittle();
    int a;
    cout << "\n\t\t\t CRAVING SOMETHING TODAY " <<endl;
    cout<<"\t\t\t 1.Yes \n\t\t\t 2.No"<<endl;
    cout<<"\nEnter your choice:";
    cin>>a;
    switch(a)
    {
            case 1:
                foodlist();
                break;
            case 2:
                  // Seed the random number generator
                srand(time(nullptr));

                // Display random data
                displayRandomFood(actualjson);
                break;
            default:
                 cout << "Invalid choice. Please try again.\n";
                secondpage();
    }
}



void foodlist()
{
    string chosenFood;
    system("cls");
    tittle();

    int i=1;
    cout<<"\t\t\tSaved food items:"<<endl;
      // Access and print JSON data
    for (const auto& food : actualjson["foods"])
    {
        cout <<"\t\t\t"<<i++<<"."<<toStringWithoutQuotes(food["name"]) << endl;
    }
    cout<<"Sorry for the trouble but please do mind the upper and lowercase"<<endl;
    cout<<"Enter your desired craving:";
    cin >> chosenFood;
    foodchoice(chosenFood);
}
void foodchoice(string chosenFood)
{
    int option;
    system("cls");
    tittle();
    cout << "\t\t\tPlaces that serve " << chosenFood << endl << endl;
    int i = 1;

    // Search for the chosen food item
    bool found = false;
    for (const auto& food : actualjson["foods"])
    {
        if (toStringWithoutQuotes(food["name"]) == chosenFood)
        {
            // Print related restaurants and ratings
            found = true;
            for (const auto& restaurant : food["restaurants"])
            {
                cout << "\t\t\t" << i++ << ". Restaurant: " << toStringWithoutQuotes(restaurant["name"]) << endl;
                cout << "\t\t\t   Rating: " << restaurant["rating"] << endl << endl;
            }
            break;
        }
    }


    // If the chosen food is not found
    if (!found)
    {

        cout << "Sorry!! We lack data on the food item you desired." << endl;
        cout << "Enter to continue:";
        cin.ignore();
        cin.get();
        foodlist();

        cin>>chosenFood;
        foodchoice( chosenFood);
        return; // Exit the function
    }

    cout << "Want us to recommend a specific place for the day?" << endl;
    cout << "1. Yes\n2. No" << endl;
    cout << "Your choice: ";
    cin >> option;

    switch (option)
    {
    case 1:
        displayRandomRestaurant(actualjson, chosenFood);
        cout<<"Enter to continue:";
        cin.ignore();
        cin.get();
        lastpage();
        break;
    case 2:
        lastpage();
        break;
    default:
        cout << "Invalid choice!!" << endl;
    }

}
void lastpage()
{
    system("cls");
        tittle();
        cout << "\t\t\tHope you enjoy your meal!!" << endl;
        cout << "\t\t\t\tTHANK YOU" << endl;
}
