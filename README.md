# Qt WebApp Backend

This project is a backend application for a web application, built using the Qt framework and the QtWebApp library. It includes user authentication (login and registration) and provides functionality for storing and retrieving messages. The backend interacts with a PostgreSQL database and handles JWT (JSON Web Token) authentication using the jwt-cpp header-only library.

## Features

- User Registration
- User Login
- JWT-based Authentication
- Store Messages from POST Requests
- Retrieve Messages with GET Requests
- PostgreSQL Database Integration

## Dependencies

- Qt Framework
- QtWebApp Library
- jwt-cpp Library
- PostgreSQL

## Installation

### Prerequisites

- Qt installed on your system
- PostgreSQL database setup and running
- C++ compiler

### Step-by-Step Installation

1. Clone the repository:
    ```sh
    git clone git@github.com:MiladSabri74/QTwebAppTest.git
    cd QTwebAppTest
    ```

2. Install dependencies:
    - Follow the instructions to install Qt and QtWebApp library.
    - Ensure PostgreSQL is installed and running.
    - Include the jwt-cpp header-only library in your project.

3. Configure the PostgreSQL database:
    - Create a database and a `users` table with the necessary schema:
      ```sql
      CREATE TABLE users (
          id SERIAL PRIMARY KEY,
          username VARCHAR(50) UNIQUE NOT NULL,
          password_hash VARCHAR(255) NOT NULL
      );
      ```

4. Configure the application:
    - Update the database connection settings in your project source code.

5. Build the project:
    ```sh
    qmake
    make
    ```

## Usage

### Starting the Server

Run the compiled application:
```sh
./QTwebAppTest
```
## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any changes or enhancements.

## Acknowledgements

    Qt Framework
    QtWebApp Library
    jwt-cpp Library
    PostgreSQL

## Contact

For any inquiries or questions, please contact milad sabri at milad.sabri74@gmail.com
  
