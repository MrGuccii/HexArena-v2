extends Node2D

var speed: float = 300.0
var sync_timer: float = 0.0
var sync_rate: float = 1.0 / 20.0 # 20 network package per second

func _draw():
	draw_circle(Vector2.ZERO, 20.0, Color.GREEN);
	
func _process(delta: float):
	var target = get_global_mouse_position()
	
	var direction = global_position.direction_to(target)
	
	if global_position.distance_to(target) <= 5.0:
		direction = Vector2.ZERO
		
	sync_timer += delta
	if sync_timer >= sync_rate:
		sync_timer = 0.0
		send_position_to_server(direction)
		
func send_position_to_server(direction: Vector2):
	var main_node = get_parent()
	
	if main_node and main_node.socket.get_ready_state() == WebSocketPeer.STATE_OPEN:
		var payload = {
			"action": "direction",
			"dx": snapped(direction.x, 0.0001),
			"dy": snapped(direction.y, 0.0001)
		}
		main_node.socket.send_text(JSON.stringify(payload))
	
