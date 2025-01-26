# myTeams
This program is a simple command-line interface that allows users to interact with a server and perform various tasks. The program is designed to be user-friendly and easy to use, with clear and concise commands that can be executed by the client. You can send message to other users, create group called team, create channel, create thread, subscribe to a team, unsubscribe from a team.

## User commands
The following commands are available for use by the client:

- `/help`: show help
- `/login` [“user_name”]: set the user_name used by client
- `/logout`: disconnect the client from the server
- `/users`: get the list of all users that exist on the domain
- `/user` [“user_uuid”]: get details about the requested user
- `/send` [“user_uuid”] [“message_body”]: send a message to specific user
- `/messages` [“user_uuid”]: list all messages exchanged with the specified user
- `/subscribe` [“team_uuid”]: subscribe to the events of a team and its sub directories (enable reception of all events from a team)
- `/subscribed` ?[“team_uuid”]: list all subscribed teams or list all users subscribed to a team
- `/unsubscribe` [“team_uuid”]: unsubscribe from a team
- `/use` ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”]: Sets the command context to a team/channel/thread
- `/create`: based on the context, create the sub resource (see below)
- `/list`: based on the context, list all the sub resources (see below)
- `/info`: based on the context, display details of the current resource (see below)

## Protocol
The program uses a simple text-based protocol to communicate with the server. The protocol is defined in the **docs/protocol.txt** file, which contains detailed information about the format and structure of messages exchanged between the client and server.

## Developer Guide
To add new commands to the program, follow these steps:

- Add a new function and a new command to the **handlers** functions array in **myteams_server.h**

- If you need to send an answer to the client put your string in **clean_answer()** function using a code based on the protocol.

### Structs

- `user_s`: List of informations about users. When server is start every users are load and the structs are init.

- `private_message_s`: List of messages between users. When server is start every private message are load and the structs are init.

- `user_register_channel_s`: List of users subscribed to a team.

- `comment_s`: List of comments present in a thread.

- `thread_s`: List of threads present in a channel.

- `channel_s`: List of channels present in a team.

- `team_s`: List of teams present in the server.

- `client_s`: List of informations about a connected socket. Create when a socket is connect on the server.

- `server_s`: Struct initialize when the server is start. Contain every informations about the server socket.

- `myteams_s`: Principal struct contain every informations about everythings.

By following these steps, developers can easily add new commands to the program and expand its functionality.

## Example Usage

Here is an example of how to use the program:

- Start the program by running the **./myteams_server [port]** command.
- Connect to a server using the **./myteams_cli** command. For example, **./myteams_cli [server ip] [port]**.
- List all available commands on the server using the **/help** command.
- Connect/Create a user on the server using the **/login** command. For example, **/login Albert**.
- Disconnect from the server using the **/logout** command.
- Exit the program using **Ctrl + C**.

## Contact
For any questions or issues, please contact the development team at [louislafosse](https://github.com/louislafosse), [Lopotiron](https://github.com/Lopotiron), [Nah700](https://github.com/Nah700).

## License
This program is licensed under the MIT License.

## Contributing
We welcome contributions to this project! To contribute, please follow these steps:

- Fork this repository.
- Create a new branch for your changes.
- Make your changes and commit them.
- Push your changes to your forked repository.
- Create a pull request.
- We will review your changes and merge them into the main repository if they are appropriate.

## Security
If you discover a security vulnerability in this project, please report it to us immediately. We will work with you to resolve the issue and disclose it responsibly.

## Legal
This project is provided "as is" without warranty of any kind, either express or implied. In no event shall the authors or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, arising from, out of, or in connection with this project or the use or other dealings in this project.

This project is licensed under the MIT License.

This project is copyright © 2024 by **Julien Dufaur, Louis Lafoss, Nahim Kandari**. All rights reserved.