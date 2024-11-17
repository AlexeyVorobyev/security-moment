terraform {
  required_providers {
    twc = {
      source = "tf.timeweb.cloud/timeweb-cloud/timeweb-cloud"
    }
  }
  required_version = ">= 0.14"
}

variable "token" {
 type = string
 description = "Token for timeweb"
}

provider "twc" {
  token = var.token
}


resource "twc_project" "lab8" {
  name        = "Lab 8 security moment"
  description = "Lab 8 project for security moment"
}

data "twc_os" "os" {
  name    = "ubuntu"
  version = "22.04"
}

data "twc_presets" "preset" {
  price_filter {
    from = 300
    to   = 500
  }
}

data "twc_ssh_keys" "ssh_key" {
  name="lexxv@lexxv-work-sec-moment"
}

resource "twc_server" "server_1" {
  name  = "server"
  os_id = data.twc_os.os.id

  preset_id = data.twc_presets.preset.id

  project_id = resource.twc_project.lab8.id

  ssh_keys_ids = [data.twc_ssh_keys.ssh_key.id]
}

resource "twc_server_ip" "ip_1" {
  source_server_id = twc_server.server_1.id

  type = "ipv4"
}

output "ipv4_1" {
  value = twc_server_ip.ip_1.ip
}

resource "twc_server" "server_2" {
  name  = "server"
  os_id = data.twc_os.os.id

  preset_id = data.twc_presets.preset.id

  project_id = resource.twc_project.lab8.id

  ssh_keys_ids = [data.twc_ssh_keys.ssh_key.id]
}

resource "twc_server_ip" "ip_2" {
  source_server_id = twc_server.server_2.id

  type = "ipv4"
}

output "ipv4_2" {
  value = twc_server_ip.ip_2.ip
}
