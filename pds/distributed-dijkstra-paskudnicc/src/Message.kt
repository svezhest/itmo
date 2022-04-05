package dijkstra.messages

sealed class Message

data class MessageWithData(val data: Long) : Message()
data class MessageResponse(val agreed: Boolean) : Message()

object MessageDisconnected : Message()
