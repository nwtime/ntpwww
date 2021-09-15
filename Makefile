default: public

# For production, use prodsite.toml.
# For testing, do not use prodsite.toml

public: FRC
	rm -rf public
	hugo --config config.toml,prodsite.toml

FRC:
