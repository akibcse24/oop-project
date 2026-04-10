# Banking System - Developer Notes

## Build & Run
```bash
g++ main.cpp signin.cpp admin.cpp banker.cpp client.cpp -o main.exe
./main.exe
```

## Login Credentials
- Admin: `admin` / `admin123`
- Banker: ID starts with `b` (e.g., `b1`, stored in `banker_db.txt`)
- Client: ID starts with `ac` (e.g., `ac1`, stored in `clients_db.txt`)

## Architecture
- Entry point: `main.cpp` - creates `User*` via `login()`, calls polymorphic `display()` and `menu()`
- Base class: `User` (abstract with pure virtual `display()`, `menu()`)
- Derived classes: `Client`, `Banker`, `Admin`
- Encryption: XOR-based in `user.h` using per-instance `key` member

## Data Files (tab-separated: Name | ID | Password | Balance/Status)
- `clients_db.txt` - Client accounts (initial balance: 0)
- `banker_db.txt` - Banker accounts (initial salary: 50000)
- `hex_key.txt` - Session key

---

# Presentation Features

## OOP Concepts Demonstrated
1. **Abstract Class** - `User` with pure virtual `display()` and `menu()`
2. **Inheritance** - `Client`, `Banker`, `Admin` inherit from `User`
3. **Polymorphism** - Base `User*` calls derived class methods
4. **Encapsulation** - Data members private, accessed via methods
5. **Templates** - `modDB()` function template in `client.cpp`
6. **Lambda Functions** - Used with `modDB()` for withdraw/deposit
7. **Function Overloading** - Multiple `Client::withdraw(deposit/transfer)`

---

# Class Details

## Base Class: `User` (user.h)

### Variables (Members)
| Variable | Type | Description |
|----------|------|-------------|
| `name` | `string` | User's name |
| `id` | `string` | User ID (e.g., "ac1", "b1", "admin") |
| `pwd` | `string` | Password (stored encrypted) |
| `key` | `char` | Encryption key for XOR cipher |

### Functions (Methods)
| Function | Return | Description |
|----------|--------|-------------|
| `User()` | constructor | Initializes name, id, pwd; key defaults to 'K' |
| `~User()` | virtual destructor | Ensures proper cleanup of derived classes |
| `display()` | `virtual void = 0` | Pure virtual - must be overridden |
| `menu()` | `virtual void = 0` | Pure virtual - must be overridden |
| `encrypt(string s)` | `string` | XOR encrypts string using `key` |
| `decrypt(string s)` | `string` | XOR decrypts (same as encrypt due to XOR property) |

### Friends (External functions with access)
- `updateBalance(User*, double, bool)` - Modifies client balance
- `findUser(User*, string)` - Searches for user in database
- `updateDB(User*, string, string)` - Updates database entry

---

## Derived Class: `Client` (client.h, client.cpp)

### Inherits from: `User`

### Functions (Methods)
| Function | Parameters | Description |
|----------|------------|-------------|
| `Client()` | `n, i, p` (strings) | Constructor - passes to base User |
| `display()` | override | Prints "CLIENT: name (id)" |
| `menu()` | override | Shows: View, Withdraw, Deposit, Transfer, Exit |
| `viewAccount()` | none | Displays user's account details from DB |
| `withdraw()` | `double amt` | Deducts amount from balance |
| `deposit()` | `double amt` | Adds amount to balance |
| `transfer()` | `string to, double amt` | Transfers to another client ID |

### Global Helper Functions (in client.cpp)
| Function | Description |
|----------|-------------|
| `updateBalance(User* u, double amt, bool add)` | Reads `clients_db.txt`, finds user by ID, updates balance (add=true for deposit, false for withdraw), writes back |

---

## Derived Class: `Banker` (banker.h, banker.cpp)

### Inherits from: `User`

### Functions (Methods)
| Function | Parameters | Description |
|----------|------------|-------------|
| `Banker()` | `n, i, p` (strings) | Constructor - passes to base User |
| `display()` | override | Prints "BANKER: name (id)" |
| `menu()` | override | Shows: Add, Remove, View, Block, Exit |
| `addAccount()` | `string cn` | Creates new client account (auto-generates ID acX, password, balance=0) |
| `removeAccount()` | `string uid` | Deletes client by ID from database |
| `viewAccounts()` | none | Lists all client accounts |
| `blockTransfer()` | `string uid` | Sets client status to BLOCKED |

---

## Derived Class: `Admin` (admin.h, admin.cpp)

### Inherits from: `User`

### Variables
| Variable | Type | Description |
|----------|------|-------------|
| `key` (hidden) | `char` | Private override - admin can change encryption key |

### Functions (Methods)
| Function | Parameters | Description |
|----------|------------|-------------|
| `Admin()` | `n, i, p` | Constructor - sets key to 'K' |
| `display()` | override | Prints "ADMIN: name" |
| `menu()` | override | Shows: Hax, Add, Remove, View, Exit |
| `addBanker()` | `string n` | Creates new banker (auto-generates ID bX, salary=50000) |
| `removeBanker()` | `string i` | Deletes banker by ID |
| `viewBankers()` | none | Lists all banker accounts |
| `setKey()` | `char k` | Changes encryption key (unique admin feature) |

---

## Authentication: `signin.cpp`

### Functions
| Function | Description |
|----------|-------------|
| `init()` | Creates `clients_db.txt` and `banker_db.txt` with headers if they don't exist |
| `verify(User* u, string db)` | Searches database file for matching ID, decrypts stored password, compares with input |
| `login()` | Main auth flow: prompts for username/password, checks admin hardcoded credentials OR creates Client/Banker based on ID prefix ("ac"=Client, "b"=Banker), calls verify(), allows 3 attempts |

---

## Entry Point: `main.cpp`

```cpp
int main() {
    User* u = login();        // Returns Admin*, Banker*, or Client*
    if(!u) return 1;          // Login failed
    u->display();             // Polymorphic: prints user type
    u->menu();                // Polymorphic: shows appropriate menu
    delete u;                 // Clean up heap memory
    return 0;
}
```

---

## Database Format

### clients_db.txt
```
N   I   P       B
ac1 encrypted  1000
ac2 encrypted  500
```

Columns: `Name | ID | Password (XOR encrypted) | Balance`

### banker_db.txt
```
N   I   P       S
b1  encrypted  50000
```

Columns: `Name | ID | Password (XOR encrypted) | Salary`

---

## User Menus

### Client (ac1)
1. View Account - Shows name, ID, encrypted password, balance
2. Withdraw - Input amount, deducts from balance
3. Deposit - Input amount, adds to balance
4. Transfer - Input recipient ID and amount
5. Exit

### Banker (b1)
1. Add Account - Input client name, auto-creates account
2. Remove Account - Input client ID to delete
3. View Accounts - Lists all clients
4. Block Transfer - Input client ID to block
5. Exit

### Admin (admin)
1. Hax - Change encryption key
2. Add Banker - Input name, auto-creates banker
3. Remove Banker - Input banker ID to delete
4. View Bankers - Lists all bankers
5. Exit