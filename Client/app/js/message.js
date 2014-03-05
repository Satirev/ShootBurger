var message = (function() {
	var helloAnswer = function(data) {
			console.log('[helloAnswer]');
			if(data.player.name !== undefined && data.player.color !== undefined) {
				game.player.create(data.player.name, data.player.color);
			}
			else {
				console.log('---> data.name or data.color not found');
			}
		},
		initGame = function(data) {
			console.log('[initGame]');
			
			if(data.gameID !== undefined && data.map !== undefined && data.players !== undefined && data.gameType !== undefined) {
				game.create(data.gameID, data.map, data.players, data.gameType);
				scripts.switchScenes('#SceneGame');
			}
			else {
				alert('---> data.gameID, data.map, data.players or data.gameType not found');
			}
			
			game.initGame();
			var i,
			 	len = data.players.length;
			for(i = 0; i < len; i++){
				console.log(data.players[i].color.toString(16));
				game.score.update(data.players[i].name, 0, "#" + scripts.dec2hex(data.players[i].color));
			}
		},
		startGame = function(value) {
			console.log('[startGame]');
			bgAnimate.stop();
			game.startGame(value);
		},
		interval = function(data) {
			if(data.time !== undefined && data.balls !== undefined) {
				game.getScene().drawBalls(data.balls);
			}
			else {
				console.log('---> data.time or data.balls not found');
			}
		},
		target = function(data) {
			if(data.type !== undefined && data.id !== undefined && data.position !== undefined) {
				game.target(data);
			}
			else {
				console.log('---> data.typ, data.id or data.position not found');
			}
		},
		score = function(data) {
			console.log('[score]');
			if(data.playerName !== undefined && data.score !== undefined) {
				var color = $.map(game.getPlayers(), function(val) {
					return val.name == data.playerName ? val.color : false;
				});
				
				game.score.update(data.playerName, data.score, "#" + scripts.dec2hex(color));
			}
			else {
				console.log('---> data.playerName or data.score not found');
			}
		},
		gameEnd = function(data) {
			if(data.winner !== undefined) {
				game.score.hide();
				game.result.show();
				setTimeout(function() {
					game.result.hide();
					game.endGame();
					scripts.switchScenes('#SceneMenu');
					bgAnimate.startAnimate();
				}, 10000);
				
				//TODO
				//wstrzymanie renderowania
			}
			else {
				console.log('---> data.winner not found');
			}
		};
		
	this.process = function(json) {
		json = json.data;
		json = JSON.parse(json);
		if(json.type !== undefined) {
			switch (json.type) {
			case 'HelloAnswer':
				helloAnswer(json.data);
				break;
			case 'InitGame':
				initGame(json.data);
				break;
			case 'StartGame':
				startGame(json.data);
				break;
			case 'Interval':
				interval(json.data);
				break;
			case 'Target':
				target(json.data);
				break;
			case 'Score':
				score(json.data);
				break;
			case 'GameEnd':
				gameEnd(json.data);
				break;
			default:
				console.log('---> unrecognized json.type');
				break;
			}
		} else {
			console.log('---> json.type not found');
		}
	};
	
	this.sendShot = function(pow, vector) {
		console.log('[shot sending...]');
		
		// #define {x: int,   y: int,   z: int } VECTOR
		
		var json = {
			"type" : "Shot",
			"data" : {
				"power" : pow,
				"vec" : vector
			}
		};
		websockets.sendMessage(JSON.stringify(json));
	};
	
	this.loadingComplete = function(){
		console.log('loading Complete');
		var json = {
			type : 'Ready',
			data : {
				status : true
			}
		};	
		websockets.sendMessage(JSON.stringify(json));
	};

	return this;
})();