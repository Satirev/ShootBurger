var scripts = (function() {
	var Scripts = function(){
		this.switchScenes = function(destScene) {
			var srcScene = app.router.currentScene;
			app.scene.hide(srcScene);
			app.scene.show(destScene);
			app.router.currentScene = destScene;
		};
		
		this.showScenes = function(destScene) {
			console.log(destScene);
			app.scene.show(destScene);
		};
		
		this.showPopUp = function(text, srcScene, act) {
			sourceScene = srcScene;
			action = act;
			
			scripts.showScenes('#ScenePopUp');
			$('#PopUpCase span').text(text);
		};

		this.dec2hex = function(value) {
			var hex = Number(value).toString(16);
			hex = "000000".substr(0, 6 - hex.length) + hex; 
			return hex;
		};
	};
	
	return new Scripts;
})();