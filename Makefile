default: public

public: FRC
	rm -rf public
	hugo --config config.toml,private.toml

FRC:
