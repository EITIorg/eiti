# Local settings
You might need to remove from config.yaml (especially on macOS)

"hooks:
  post-start:
    - exec: a2enmod proxy_http && apache2ctl graceful"
