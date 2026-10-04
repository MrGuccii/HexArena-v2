extends Node2D

var socket = WebSocketPeer.new()

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	print("Starting...")
	
	var tls_option = TLSOptions.client_unsafe()
	var err = socket.connect_to_url("wss://localhost:7000", tls_option)
	
	if err != OK:
		print("Error while connecting to server!")
	else:
		print("Connecting to server...")

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	socket.poll()
	var state = socket.get_ready_state()
	
	if state == WebSocketPeer.STATE_OPEN:
		# If there is an incoming message, print it to the console
		while socket.get_available_packet_count() > 0:
			var message = socket.get_packet().get_string_from_utf8()
			print("Server: ", message)
	elif state == WebSocketPeer.STATE_CLOSED:
		var code = socket.get_close_code()
		var reason = socket.get_close_reason()
		print("Connection lost! Code: ", code, " Reason: ", reason)
		set_process(false)
