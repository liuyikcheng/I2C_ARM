PROJECT_CEEDLING_ROOT = "vendor/ceedling"
load "#{PROJECT_CEEDLING_ROOT}/lib/ceedling.rb"

load "scripts/helper.rb"

# With this now we can choose which '.yml' configuration file to be loaded by
# issuing e.g.:
#     rake project=./myproject.yml test:all
#
project_file = get_value_from_env('project', './project.yml')

Ceedling.load_project(config: project_file)
#p @ceedling[:project_config_manager].config_hash   # Contain the loaded YAML file's content

# The following must be loaded after Ceedling.load_project()
load_extra_scripts(project_file)

desc 'Build and deploy'
task :build_and_deploy do
  # Build and deploy
  #system "rake project=myproject.yml hw:flash"
  system "rake hw:flash"
end

task :default => %w[ build_and_deploy test:all ]
