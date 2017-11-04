
#define ZERO_EXCEPTION_ID 0
#define OVERFLOW_EXCEPTION_ID 4
#define INVALID_OPCODE_EXCEPTION_ID 6

static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();

	else if (exception == INVALID_OPCODE_EXCEPTION_ID)
		op_code();
}

static void zero_division() {
	// Handler para manejar excepcíon
}
