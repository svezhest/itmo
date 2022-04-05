package mutex

/**
 * Distributed mutual exclusion implementation.
 * All functions are called from the single main thread.
 *
 * @author Александр Крюков
 */
class ProcessImpl(private val env: Environment) : Process {
    enum class Type { REQ, OK }

    private var isHungry = false

    private val dirty = BooleanArray(env.nProcesses + 1)

    private val hasFork = BooleanArray(env.nProcesses + 1)

    private val smbdWantsFork = BooleanArray(env.nProcesses + 1)

    private val others = (1..env.nProcesses).minus(env.processId)

    init {
        others.forEach { i ->
            dirty[i] = true
            hasFork[i] = i < env.processId
            smbdWantsFork[i] = false
        }
    }

    private fun hasAllForks(): Boolean {
        return others.all { i -> hasFork[i] }
    }

    private fun eat() {
        env.locked()
        isHungry = false
        others.forEach { i -> dirty[i] = false }
    }

    override fun onMessage(srcId: Int, message: Message) {
        message.parse {
            val type = readEnum<Type>()
            if (type == Type.REQ) {
                if (dirty[srcId] && hasFork[srcId]) {
                    dirty[srcId] = false
                    hasFork[srcId] = false
                    env.send(srcId) {
                        writeEnum(Type.OK)
                    }
                    if (isHungry) {
                        env.send(srcId) {
                            writeEnum(Type.REQ)
                        }
                    }
                } else {
                    smbdWantsFork[srcId] = true
                }
            } else if (type == Type.OK) {
                hasFork[srcId] = true
                if (isHungry && hasAllForks()) {
                    eat()
                }
            }
        }
    }

    override fun onLockRequest() {
        isHungry = true
        if (hasAllForks()) {
            eat()
        } else {
            others.filter { i -> !hasFork[i] }.forEach { i ->
                env.send(i) {
                    writeEnum(Type.REQ)
                }
            }
        }
    }

    override fun onUnlockRequest() {
        env.unlocked()
        isHungry = false
        others.forEach { i ->
            if (smbdWantsFork[i]) {
                dirty[i] = false
                hasFork[i] = false
                smbdWantsFork[i] = false
                env.send(i) {
                    writeEnum(Type.OK)
                }
            } else {
                dirty[i] = true
            }
        }
    }
}