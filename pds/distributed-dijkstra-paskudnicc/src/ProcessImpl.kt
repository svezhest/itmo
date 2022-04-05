package dijkstra

import dijkstra.messages.*
import dijkstra.system.environment.Environment

class ProcessImpl(private val environment: Environment) : Process {
    private var result: Long? = null
    private var childCount: Int = 0
    private var balance: Int = 0
    private var parentId: Int = -1

    private fun sendMessage(id: Int, m: Message) {
        balance++
        environment.send(id, m)
    }

    private fun sendDistance(neighbour: Map.Entry<Int, Long>) {
        sendMessage(neighbour.key, MessageWithData(result!! + neighbour.value))
    }

    private fun updateNeighbours() {
        environment.neighbours.forEach { n -> sendDistance(n) }
        if (checkGreen()) {
            disconnect()
        }
    }

    private fun checkGreen(): Boolean {
        return childCount == 0 && balance == 0
    }

    private fun disconnect() {
        if (parentId == -1) {
            environment.finishExecution()
        } else {
            environment.send(parentId, MessageDisconnected)
            parentId = -1
        }
    }

    override fun onMessage(srcId: Int, message: Message) {
        if (message is MessageWithData) {
            if (result == null || message.data < result!!) {
                if (parentId == -1) {
                    environment.send(srcId, MessageResponse(true))
                    parentId = srcId
                } else {
                    environment.send(srcId, MessageResponse(false))
                }
                result = message.data
                updateNeighbours()
            } else {
                environment.send(srcId, MessageResponse(false))
            }
            return
        } else if (message is MessageDisconnected) {
            childCount--
        } else if (message is MessageResponse) {
            balance--
            if (message.agreed) {
                childCount++
            }
        } else {
//            raise exception
        }
        if (checkGreen()) {
            disconnect()
        }
    }

    override fun getDistance(): Long? {
        return result
    }

    override fun startComputation() {
        result = 0
        updateNeighbours()
    }
}