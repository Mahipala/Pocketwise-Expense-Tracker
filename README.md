# PocketWise Expense Tracker — Data Structures in C

A responsive expense tracker website and a C console program demonstrating a **singly linked list**.

## Included files
- `index.html`: webpage structure
- `style.css`: responsive UI styling
- `app.js`: interactive web demo (browser localStorage)
- `expense_tracker.c`: linked-list C program (add, display, search, delete, totals)

## Run the website
1. Extract the ZIP folder.
2. Open `index.html` in a browser (Chrome, Edge, Firefox).
3. Add expenses with title, amount, category, and date.
4. Search transactions or filter by category. Click the × at the end of a row to delete.
5. Category overview and summary totals update automatically. Data is saved in your browser local storage.

No server or dependencies are required for the website.


## Run the C program
### Linux / macOS
```bash
gcc expense_tracker.c -o expense_tracker
./expense_tracker
```
### Windows with MinGW GCC
```bash
gcc expense_tracker.c -o expense_tracker.exe
expense_tracker.exe
```

Menu features: Add expense, display expenses, summary total/average, search by title or category, delete by ID.

## Linked list explanation
The C implementation uses `Expense` nodes. Each node stores an ID, title, category, amount, date, and pointer to the next node.
- Add: insert at the head — O(1)
- Display/search: traverse the nodes — O(n)
- Delete: traverse to target and relink pointers — O(n)
- Total/average: traverse all entries — O(n)

The web frontend is a browser-side demo that uses JavaScript and local storage. The C linked-list program is a separate console implementation of the same expense-tracker features (not a C web server).
