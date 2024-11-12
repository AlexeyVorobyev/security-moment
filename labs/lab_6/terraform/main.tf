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


resource "twc_project" "lab6" {
  name        = "Lab 6 security moment"
  description = "Lab 6 project for security moment"
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

resource "twc_vpc" "vpc" {
  name = "Lab 6 VPC"
  description = "Lab 6 VPC"
  subnet_v4 = "192.168.0.0/24"
  location = "ru-1"
}

resource "twc_server" "server_1" {
  name  = "server"
  os_id = data.twc_os.os.id

  preset_id = data.twc_presets.preset.id

  project_id = resource.twc_project.lab6.id

  local_network {
    id = twc_vpc.vpc.id
  }
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

  project_id = resource.twc_project.lab6.id

  local_network {
    id = twc_vpc.vpc.id
  }
}

resource "twc_server_ip" "ip_2" {
  source_server_id = twc_server.server_2.id

  type = "ipv4"
}

output "ipv4_2" {
  value = twc_server_ip.ip_2.ip
}
