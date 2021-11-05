default: public

# For production, use prodsite.toml.
# For testing, do not use prodsite.toml

BRANCH=`git branch | awk '{ print $$2}'`

public: FRC
	@echo "Branch: <${BRANCH}>"
	rm -rf public
	hugo --config config.toml,prodsite.toml

FRC:
