action = false;

var Router = function(){
	this.scenes = [];
	this.lastScene = null;
	this.currentScene = null;
};

Router.prototype.init = function(){

}

Router.prototype.add = function(scene, name){
	this.scenes[name] = scene;
	this.scenes[name].init = false;
}

Router.prototype.show = function(name){
	this.lastScene = this.currentScene;
	this.currentScene = name;
	if(this.scenes[name].init == false){
		this.scenes[name].init = true;
		this.scenes[name].initialize();
	}
	this.scenes[name].show();
}

Router.prototype.hide = function(name){
}


app = ( function (){
	var Application = function(){
		var self = this;
		this.player_name = false;
		this.global_ip = false;
		this.global_port = false;
		
		this.scene = ( function (){
			var Scene = function(){
				
			};

			Scene.prototype.hide = function(name){
				$(self.router.currentScene).hide();
			};

			Scene.prototype.show = function(name){
				self.router.show(name);
				$(name).show();
			};

			return new Scene();
		}());


		this.router = new Router();
	};

	

	Application.prototype.init = function(){
		this.router.init();
		this.router.add(new SceneMenu,'#SceneMenu');
		this.router.add(new SceneMenu,'#SceneMenu');
		this.router.add(new ScenePopUp,'#ScenePopUp');
		this.router.add(new SceneGame,'#SceneGame');
		this.router.add(new SceneLobby,'#SceneLobby');
		this.router.add(new SceneAbout,'#SceneAbout');
		this.router.add(new SceneInfo,'#SceneInfo');
		this.router.add(new SceneOptions,'#SceneOptions');
		this.router.add(new SceneInit,'#SceneInit');
	};

	return new Application();
}());

$(document).ready(function() { 
	History.Adapter.bind(window,'statechange',function(){ // Note: We are using statechange instead of popstate
        var State = History.getState(); // Note: We are using History.getState() instead of event.state
        if(State.data.scene !== 'undefined') {
        	scripts.switchScenes(State.data.scene);
        }
    });
	bgAnimate = new BgAnimate();
	bgAnimate.startAnimate();
	app.init();
	app.scene.show('#SceneInit');
});