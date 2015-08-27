# Authorization #
Client will send a OOB message to the master server.

`auth <nickname> <password>`

Master's responses:

`authSuccess`

`authFail`

# Registration #
Only via webinterface

# Nick Registration #
Only via webinterface

# Nick dropping #
Only via webinterface

# Account dropping #
Only via webinterface

# Guid Logic (TBD!) #
On startup, client sends its nickname and md5-hashed guid to the masterserver, which checks if they fit. This way we don't need to save password. The guid must be first saved in the webinterface, where a new one can also be retrieved from.
When connecting to a server, the client sends its md5-hashed guid to the server, which then checks the data with the master server again. Random checks while ingame are probably a good idea too.
If two different accounts use the same guid, they are both disabled until the issue is resolved by a Hazewood admin.
Invalid guids will resolve in failed logins, which will also disable a few cheats. Changing guid while playing will result in an 24 hour global ban and an admin notice.