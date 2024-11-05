terraform {
  required_providers {
    twc = {
      source = "tf.timeweb.cloud/timeweb-cloud/timeweb-cloud"
    }
  }
  required_version = ">= 0.13"
}

variable "token" {
 type = string
 description = "Token for timeweb"
}

provider "twc" {
  token = var.token
}


resource "twc_project" "lab3" {
  name        = "Lab 3 security moment"
  description = "Lab 3 project for security moment"
}

data "twc_os" "os" {
  name    = "ubuntu"
  version = "22.04"
}

data "twc_presets" "preset" {
  price_filter {
    from = 100
    to   = 300
  }
}

resource "twc_server" "server" {
  name  = "server"
  os_id = data.twc_os.os.id

  preset_id = data.twc_presets.preset.id

  project_id = resource.twc_project.lab3.id
}

resource "twc_server_ip" "ip" {
  source_server_id = twc_server.server.id

  type = "ipv4"
}

output "ipv4" {
  value = twc_server_ip.ip.ip
}
