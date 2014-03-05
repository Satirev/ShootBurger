var game = (function () {
	var player = function() {
		var name = false,
			color = false;
		
		this.create = function(_name, _color) {
			console.log('[player creating...]');
			name = _name;
			color = _color;
		};
		
		this.getName = function() {
			return name;
		};
		
		this.getColor = function() {
			return color;
		};
		
		return this;
	};
	
	var game = function(){
		var gameID = false,
			map = false,
			scene3d = false,
			players = [],
			gameType = {id : 0, value: 0};
		
		this.create = function(_gameID, _map, _players, _gameType) {
			console.log('[game creating...]');
			gameID = _gameID;
			map = _map;
			players = _players;
			gameType = _gameType;
		};
		
		this.getMap = function() {
			return map;
		};
		
		this.getGameID = function() {
			return gameID;
		};
		
		this.initGame = function(){
			scene3d = new Scene3dController('canvasContainer', message.sendShot, message.loadingComplete);
		};
		
		this.startGame = function(value){
			scene3d.startGame(value);
		};

		this.endGame = function(){
			scene3d.endGame();
		};
		
		this.target = function(data){
			scene3d.targetAction(data);
		};
		
		this.getScene = function(){
			return scene3d;
		};
		
		this.getPlayers = function() {
			return players;
		};
		
		this.getGameType = function() {
			return gameType;
		};
		
		this.player = new player();

				var timer = function() {
			var show = function() {
					$('#timer').show( "fast");
				},
				hide = function() {
					$('#timer').hide( "fast");
				};
				
			this.start = function(val, callback) {
				$("#timer p").text(val);
				show();
				var time = val;
				var result = self.setInterval(function() {
					timer();
				}, 1000);
				function timer() {
					time--;
					$("#timer p").text(time);
					if (time === 0) {
						hide();
						callback();
						window.clearInterval(result);
					}
				}
			};
			
			return this;
		};
		
		var score = function() {
			var players = [], 
				findPlayer = function(name) {
				var found = $.map(players, function(val) {
					return val.name == name ? true : false;
				});

				for ( var i = 0, len = found.length; len > i; i++) {
					if (found[i] === true) {
						return i;
					}
				}
				return false;
			}, addPlayer = function(name, score, color) {
				console.log('[game score addPlayer()]');
				var player = {
					name : name,
					color : color,
					score : score
				};

				players.push(player);
			},
			addScore = function(name, score, id) {
				var $score = $('#score'),
					color = players[id].color,
					scoreEl = '<div class="ball" style="background-color: ' + color + ';"></div><p id="score' + id + '">' + name + ': ' + score + '</p>',
					$scoreElement = $(scoreEl);
				
				$score.append($scoreElement);
			},
			updateScore = function(name, score, id) {
				var $thisScore = $('#score' + id);
				
				$thisScore.text(name + ': ' + score);
			};

			this.update = function(name, score, color) {
				var index = findPlayer(name);

				if (index !== false) {
					players[index].score = score;
					updateScore(name, score, index);
				} else {
					addPlayer(name, score, color);
					addScore(name, score, players.length - 1);
				}
			};
			
			this.show = function() {
				$('#score').show( "fast");
			};
			
			this.hide = function() {
				$('#score').hide( "fast");
			};

			return this;
		};
		
		var result = function() {
			this.show = function() {
				var result = $('#score').html();
				$('#gameResult p').html(result);
				
				$('#gameResult').show("fast");
			};
			
			this.hide = function() {
				$('#gameResult').hide("fast");
			};
			
			return this;
		};

		this.timer = new timer;
		
		this.score = new score;
		
		this.result = new result;
	};
		
	
	return new game;
})();