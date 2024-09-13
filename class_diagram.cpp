//Program by Ayen Brinas
#include <iostream>
using namespace std;


class Product {
public:
   int id;
   string name;
   double price;


   Product() {}
   Product(int id, string name, double price) : id(id), name(name), price(price) {}
};


class ShoppingCart {
public:
   Product cartItems[10];  // Array to store products in the cart
   int quantities[10];     // Array to store quantities of each product
   int itemCount;          // Number of items in the cart


   ShoppingCart() : itemCount(0) {}


   // Add a product to the cart
   void addProduct(const Product& product) {
       for (int i = 0; i < itemCount; ++i) {
           if (cartItems[i].id == product.id) {
               quantities[i]++;  // Increment quantity if product already exists in cart
               return;
           }
       }
       cartItems[itemCount] = product;  // Add new product
       quantities[itemCount] = 1;       // Set quantity to 1
       itemCount++;
   }


   // View cart contents and ask for checkout
   void viewCart(class Order orders[], int &orderCount);


   // Get the total price of the items in the cart
   double getTotal() {
       double total = 0;
       for (int i = 0; i < itemCount; ++i) {
           total += cartItems[i].price * quantities[i];
       }
       return total;
   }


   // Clear the cart after checkout
   void clearCart() {
       itemCount = 0;  // Reset the cart by setting the count to 0
   }
};


class Order {
public:
   Product orderedItems[10];  // Array to store ordered products
   int quantities[10];        // Array to store quantities of ordered products
   int itemCount;             // Number of items in the order
   double totalAmount;        // Total amount for the order


   // Default constructor
   Order() : itemCount(0), totalAmount(0) {}


   // Constructor that takes the ShoppingCart and creates an order
   Order(ShoppingCart& cart) {
       itemCount = cart.itemCount;
       totalAmount = cart.getTotal();
       for (int i = 0; i < itemCount; ++i) {
           orderedItems[i] = cart.cartItems[i];
           quantities[i] = cart.quantities[i];
       }
   }


   // View the details of the order
   void viewOrderDetails() {
       cout << "ID\tName\tPrice\tQty\n";
       for (int i = 0; i < itemCount; ++i) {
           cout << orderedItems[i].id << "\t"
                << orderedItems[i].name << "\t$"
                << orderedItems[i].price << "\t"
                << quantities[i] << endl;
       }
       cout<<endl;
       cout << "Total Amount: $" << totalAmount << endl;
   }
};


// Display products available for purchase
void displayProducts(Product products[], int size) {
   cout<<endl;
   cout<<"   Our Products"<<endl;
   cout << "ID\tName\tPrice\n";
   for (int i = 0; i < size; ++i) {
       cout << products[i].id << "\t"
            << products[i].name << "\t$"
            << products[i].price << endl;
   }
}


// View all orders placed
void viewOrders(Order orders[], int orderCount) {
   if (orderCount == 0) {
       cout << "No orders placed yet.\n";
       return;
   }


   for (int i = 0; i < orderCount; ++i) {
       cout << "------------------------\n";
       cout << "Order " << i + 1 << ":\n";
       orders[i].viewOrderDetails();
       cout << "------------------------\n";
   }
}


// Implementation of viewCart function with checkout option and total amount display
void ShoppingCart::viewCart(Order orders[], int &orderCount) {
   if (itemCount == 0) {
       cout << "Your cart is empty.\n";
       return;
   }
cout<<endl;
cout<<"         YOUR CART"<<endl;
   cout << "ID\tName\tPrice\tQty\n";
   for (int i = 0; i < itemCount; ++i) {
       cout << cartItems[i].id << "\t"
            << cartItems[i].name << "\t$"
            << cartItems[i].price << "\t"
            << quantities[i] << endl;
   }


   // Display total amount
   double total = getTotal();
   cout << "Total Amount: $" << total << endl;


   char checkoutChoice;
   cout << "Do you want to checkout the items? (Y/N): ";
   cin >> checkoutChoice;


   if (checkoutChoice == 'Y' || checkoutChoice == 'y') {
       // Proceed to checkout
       orders[orderCount] = Order(*this);  // Create a new order from the cart
       orderCount++;  // Increment the order count
       clearCart();   // Clear the cart after checkout
       cout << "Checked out successfully! Your order has been placed.\n";
   } else {
       cout << "Returning to menu...\n";
   }
}


int main() {
   Product products[3] = {
       Product(1, "TE37", 300.00),
       Product(2, "RE30", 500.00),
       Product(3, "BLKMBA", 1000.00)
   };


   ShoppingCart cart;
   Order orders[10];  // Array to store orders (up to 10 orders)
   int orderCount = 0;  // Number of orders placed
   int choice,productId;
   char addMore;
  
  


   while (true) {
       cout<<endl;
       cout<<"Welcome to South Wheelz!!";
       cout << "\nMenu:\n1. View Products\n2. View Cart\n3. View Orders\n4. Exit\n";
       cout << "Enter choice: ";
       cin >> choice;


       if (choice == 1) {
           displayProducts(products, 3);
           do {
               cout << "Enter product ID to add to cart: ";
               cin >> productId;
               bool found = false;
               for (int i = 0; i < 3; ++i) {
                   if (products[i].id == productId) {
                       cart.addProduct(products[i]);
                       found = true;
                       break;
                   }
               }
               if (!found) {
                   cout << "Product not found!\n";
               } else {
                   cout << "Product added to cart.\n";
               }
               cout << "Add another product? (Y/N): ";
               cin >> addMore;
           } while (addMore == 'Y' || addMore == 'y');
       }
       else if (choice == 2) {
           cart.viewCart(orders, orderCount);  // View cart and optionally checkout
       }
       else if (choice == 3) {
           viewOrders(orders, orderCount);  // View past orders
       }
       else if (choice == 4) {
           cout<<endl;
           cout << "THANK YOU FOR YOUR PURCHASE!\n";
           break;
       }
       else {
           cout << "Invalid choice!\n";
       }
   }


   return 0;
}
